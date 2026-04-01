import unittest
import subprocess

class TestMyProgram(unittest.TestCase):
    def test_success_case(self):
        # Запуск программы с корректными параметрами
        result = subprocess.run(
            ["../build/pushk2pre2spc", "n", "../examples/trix1.scr" , "6144"],
            capture_output=True,
            text=True )

        # Проверяем успешное завершение
        self.assertEqual(result.returncode, 0)
        # Проверяем содержимое вывода
        self.assertIn("7E8BC0800080F0807A8BC288F2FBFBE400000000000000000000000000000000", result.stdout)

    def test_error_case(self):
        # Запуск программы с некорректными параметрами
        result = subprocess.run(
            ["../build/pushk2pre2spc", "n", "../exampl/trix1.scr" , "6144"],
            capture_output=True,
            text=True )

        # Проверяем, что программа завершилась с ошибкой
        self.assertNotEqual(result.returncode, 0)
		#     # Проверяем наличие сообщения об ошибке
		#     self.assertIn("Error", result.stderr)

if __name__ == "__main__":
    unittest.main()
