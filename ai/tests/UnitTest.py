import unittest
import argparse
import sys
import multiprocessing
import subprocess
import os
import contextlib

current_dir = os.path.dirname(os.path.abspath(__file__))
sys.path.append(os.path.join(current_dir, '..'))

from src.worker import Action
from src import Server
from colorama import init, Fore, Back, Style

class SuppressPrints:
    def __enter__(self):
        self._original_stdout = sys.stdout
        self._devnull = open(os.devnull, 'w')
        sys.stdout = self._devnull

    def __exit__(self, exc_type, exc_val, exc_tb):
        sys.stdout.close()
        sys.stdout = self._original_stdout
        self._devnull.close()

class TestAction(unittest.TestCase):

    def __init__(self, methodName='runTest', id="1", team_name="t1", ip="127.0.0.1", port="4242"):
        with SuppressPrints():
            super().__init__(methodName)
            self.args = argparse.Namespace(id=id, team_name=team_name, ip=ip, port=port)
            self.server = Server.Server(self.args.ip, int(self.args.port))
            self.action = Action.Action(self.server, 5)

    def set_welcome_data(self):
        response = ""
        try:
            if self.server.check_read():
                print(self.args.team_name + "\n")
                self.server.send(self.args.team_name + "\n")
                response = self.server.recv()
                print("client-num and X Y" + response)
                if response == "ko\n":
                    return
        except Exception as e:
            print(e, file=sys.stderr)
            raise Exception("Core: Error while sending welcome data.")

    def setUp(self):
        with SuppressPrints():
            self.set_welcome_data()

    def test_multiProcessOrientation(self):
        print("----------------------------------------------------------------------")
        print(Fore.CYAN + "Test du getOrientation" + Style.RESET_ALL)
        with SuppressPrints():
            process2 = multiprocessing.Process(target=self.execute_getOrientation_bash)
            process2.start()
            test = self.action.getOrientation()
            process2.terminate()

        with self.subTest(msg="Test du getOrientation"):
            try:
                self.assertEqual(test, 'Assemble')
                print(Fore.GREEN + "OK" + Style.RESET_ALL)
            except AssertionError:
                print(Fore.RED + "ECHEC" + Style.RESET_ALL)

    def execute_getOrientation_bash(self):
        process = subprocess.Popen(["./scriptTest/getOrientation.sh", self.args.ip, self.args.port, self.args.team_name], stdout=subprocess.PIPE)
        process.communicate()

    def test_multiProcessOrientationFailed(self):
        print("\n----------------------------------------------------------------------")
        print(Fore.CYAN + "Test du getOrientationFailed" + Style.RESET_ALL)
        with SuppressPrints():
            process2 = multiprocessing.Process(target=self.execute_getOrientation_bashFailed)
            process2.start()
            test = self.action.getOrientation()
            process2.terminate()
        with self.subTest(msg="Test du getOrientationFailed"):
            try:
                self.assertNotEqual(test, 'Assemble')
                print(Fore.GREEN + "OK" + Style.RESET_ALL)
            except AssertionError:
                print(Fore.RED + "ECHEC" + Style.RESET_ALL)

    def execute_getOrientation_bashFailed(self):
        process = subprocess.Popen(["./scriptTest/getOrientationFail.sh", self.args.ip, self.args.port, self.args.team_name], stdout=subprocess.PIPE)
        process.communicate()

    def test_setOrientation(self):
        print("\n----------------------------------------------------------------------")
        print(Fore.CYAN + "Test du setOrientation" + Style.RESET_ALL)
        self.action.setOrientation(5)
        with self.subTest(msg="Conversion en majuscules"):
            try:
                test = self.action.orientation
                self.assertEqual(test, 5)
                print(Fore.GREEN + "OK" + Style.RESET_ALL)
            except AssertionError:
                print(Fore.RED + "ECHEC: Expected self.action.orientation = 5" + Style.RESET_ALL)

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("id", type=str, help="ID required for the test")
    parser.add_argument("team_name", type=str, help="Team name required for the test")
    parser.add_argument("ip", type=str, help="IP address required for the test")
    parser.add_argument("port", type=int, help="Port number required for the test")
    args = parser.parse_args()

    sys.argv[1:] = [args.id, args.team_name, args.ip, str(args.port)]
    unittest.main()

# coverage run --omit='/usr/lib/python3/dist-packages/colorama/*' -m unittest UnitTest.py
# coverage report -m