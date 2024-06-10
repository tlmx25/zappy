#!/usr/bin/env python3

import Tester as Tester
import sys

if __name__ == '__main__':
    try:
        tester = Tester.AiTester()
        tester.test_run()
    except Exception:
        raise Exception("Unexpected error.")
    