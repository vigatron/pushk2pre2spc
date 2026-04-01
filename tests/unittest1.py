import unittest
import subprocess
import os

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
BUILD_DIR = os.path.join(BASE_DIR, "..", "build")
EXAMPLES_DIR = os.path.join(BASE_DIR, "..", "examples")

class TestMyProgram(unittest.TestCase):
    def test_success_case(self):
        result = subprocess.run(
            [os.path.join(BUILD_DIR, "pushk2pre2spc"), "n", os.path.join(EXAMPLES_DIR, "trix1.scr"), "6144"],
            capture_output=True,
            text=True
        )
        self.assertEqual(result.returncode, 0)
        self.assertIn("7E8BC0800080F0807A8BC288F2FBFBE400000000000000000000000000000000", result.stdout)

    def test_error_case(self):
        result = subprocess.run(
            [os.path.join(BUILD_DIR, "pushk2pre2spc"), "n", os.path.join(BASE_DIR, "..", "exampl", "trix1.scr"), "6144"],
            capture_output=True,
            text=True
        )
        self.assertNotEqual(result.returncode, 0)

if __name__ == "__main__":
    unittest.main()
