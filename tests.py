import subprocess

def run(jarraString):
    process = subprocess.Popen(["./jarra", "-s", jarraString, "-nh"], stdout=subprocess.PIPE)
    output, error = process.communicate()
    if error:
        print(error)
    return output.strip()


tests = [
    # Basic Type Recognition
    ("", "None"),
    ("5","5"),
    ("1234", "1234"),
    ("\"string!\"","string!"),
    ("4.567", "4.567"),

    # Basic Operations
    ("5 + 6", "11"),
    ("5 + 6 / 3", "7"),
    ("5 * 6 / 3 - 2", "8"),
    ("4.4 / 2 + 1.8", "4.0"),
    ("(\"a string\" + 5) * (1 + 1)", "a string5a string5"),
    ("-90+-20",    "-110"),
    ("90/-3",   "-30"),
    ("80/4+4/2-5*6",   "-8"),
    # Float Operations
    ("2.5 + 2.5",  "5.0"),
    ("2.5 * 2",    "5.0"),
    # String Operations
    ("\"abc\"+\"def\"",    "abcdef"),
    ("\"abc\"*3",  "abcabcabc"),
    # Bool Operations
    ("bool(5+6-11)",   "False"),
    ("bool(5+6+11)",   "True"),
    ("bool(\"hello\")",    "True"),
    ("bool(\"\")", "False"),
    ("bool([])",   "False"),
    ("bool([1])",  "True"),
    ("bool(3.5-3.5)",   "False"),
    ("bool(3.5+3.5)",  "True"),
    ("True && False || True",  "True"),
    ("False && True",  "False"),
    ("\"hello\" || \"\" && []",    "True"),
    ("!1", "False"),
    ("!!!!!1", "False"),
    ("None && None", "False"),
    ("None || True", "True"),
    ("0 && 1", "False"),
    ("1 && -1", "True"),
    ("-1.1 && 1.4", "True"),
    ("\"a\" && \"\"", "False"),
    ("None || 1", "True"),
    # Logic Operators
    ("5 == 5.0", "True"),
    ("5.0 == 5", "True"),
    ("3 == \"hello!\"", "False"),
    ("5 == 4.99", "False"),
    ("\"abc\" == \"abc\"", "True"),
    ("5 == \"5\"", "False"),
    ("None == 6", "False"),
    ("None == None", "True"),
    # List Operations
    ("1,2,3",  "[1, 2, 3]"),
    ("[1,2,3]",    "[1, 2, 3]"),
    ("[]", "[]"),
    ("[5.6]",  "[5.6]"),
    ("[[1],2]",    "[[1], 2]"),
    ("[[1]][0][0]",    "1"),
    # List Assignment
    ("a = [1,2,3]; a[1] = 5; a",   "[1, 5, 3]"),
    ("(b=[1,2,4])[1] = b[2] - 1;b",  "[1, 3, 4]"),
    # Variable Operations
    ("a = b = c = d = 5; a = 7; a + b",    "12"),
    # If and While Expressions
    ("x = 5; y = False; if( x && y ) { x = 4 }; x",    "5"),
    ("x = 0; y = 1; while (x < 3) { x = x + 1; y = y * 2; y }",  "8"),
    # Code Blocks
    ("{ 1 + 2 }()", "3"),
    ("a = { 1 + 2 }; a()", "3"),
    ("a = { b }; a()", "None"),
    ("a = { b }; b = \"hello!\"; a()", "hello!"),
    ("a = { b }; a( b = 2 )", "2"),
    ("a = { b = 4 }; b = 2; a(); b", "2"),
    ("a = { x + 1 }; a( x = 2 ) + a( x = 6 )", "10"),
    ("","None")
]

tests_passed = 0

for test in tests:
    code = test[0]
    expected = test[1]
    result = run(code)
    if result != expected:
        print("Failed Test: '" + code + "' => '" + result + "', expected: " + expected)
    else:
        tests_passed = tests_passed + 1
print("Finished Testing. Passed {} / {} tests".format(tests_passed, len(tests)))