#!/usr/bin/env python3
import subprocess
import os
import sys
sys.path.append("../lib/")
sys.path.append("../array/")

import json_parser
import pos
import cli
import test_result
import CREATE_ARRAY_BASIC

def set_result(detail):
    code = json_parser.get_response_code(detail)
    result = test_result.expect_true(code)
    out = detail
    with open(__file__ + ".result", "w") as result_file:
        result_file.write(result + " (" + str(code) + ")" + "\n" + detail)

def execute():
    CREATE_ARRAY_BASIC.execute()
    out = cli.scan_device()
    # out = cli.array_info(CREATE_ARRAY_BASIC.ARRAYNAME)
    print(cli.list_array())
    return out

if __name__ == "__main__":
    test_result.clear_result(__file__)
    out = execute()
    set_result(out)
    pos.kill_pos()