#!/usr/bin/env python3

import Tester as Tester
import UnitTest as UnitTest
import sys


if __name__ == '__main__':
    try:
        tester = Tester.AiTester()
        tester.test_run()
        unittest = UnitTest.TestAction()
        unittest.set_welcome_data()
        unittest.test_multiProcessOrientation()
        unittest.test_setOrientation()
        sys.exit(0)
    except Exception:
        raise Exception("Unexpected error.")
    