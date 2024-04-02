﻿#include<iostream>
#include<stdlib.h>
#include<exception>
#include<time.h>
#include<limits>

/* ОБРАБОТКА ИСКЛЮЧЕНИЙ
*	- конструкции
*	- способы созданий и передачи исключений
*	- встроенные в язык исключения
*	- типы исключений
*	- рекомендации по взаимодействию с исключениями в программе
* Ключевые слова языка
* 
* throw try catch
* 
* try-блок может экранировать и передать в catch только ошибки,
* сгенерированные внутри программы/
* 
* Для неизвестных ошибок используется конструкция catch(...)
* 
* категория ошибок операционной системы runtime_error не может
* быть обработана внутри приложенияи её надо предотвращать
* 
* Правила по внедрению исключений в программу
* 1. Не обрабатываем исключение по параметрам, которыми мы не владеем
*    Не обрабатываем искл., если мы их не породили. В этом случае 
*    исп. только throw-конструкция с описанием, что пошло не так
* 2. try-catch исп. только в коде, который не уверен, что его данные
*    могут быть корректно обработаны внешним кодом
* 3. Не использовать базовые типы для ловли исключений
*    библиотека <exception>, либо пользовательские классы исключений
*	 Базовые типы в исключениях будут заставлять пользователей листать 
	 "толмуды", чтобы узнать, что тот или иной код ошибки означает

	Типы исключений:
	1. runtime_error - живут в операционке и не могут быть обработаны
	2. программные исключения:
		2.1 logic_exception
			invalid_argument (неправильные аргументы: ошибочные аргументы ф.)
			damain_error (доменная ошибка: игровая или бизнес логика)
			length_error (ошибки некорректного указания размера коллекции)
			out_of_range (выход за пределы диапазона)
		2.2 runtime_error (ошибки внутри библиотек, слом программы на системном уровне)
			range_error (обработка коллекции на системном уровне)
			overflow_error (ошибка переполнения типа данных при достижении предельного значения типа данных)
			underflow_error (если пользователь пытается преодолеть максимальное значение)
			regex_error 
			system_error (по маске строки ищут вхождение в другом месте)
		2.3 bad_typeid - ошибки определния типов
		2.4 bad_cast
		2.5 bad_alloc
		2.6 bad_exception - проблема при генерации исключения

   int Summ2(int a, int b) noexcept {}, noexcept пишется, когда компилятор должен пропустить исключения
*/

void F00(int a) {
	if (a){
		throw std::exception("Bad luck");
	}
}

void F01(int a) {
	if (a) {
		// Низкоуровневый инструментарий, пока использовать не будем
		//throw std::make_exception_ptr(std::exception("Bad luck"));
		throw std::exception("Bad luck");
	}
}

int Summ(int a, int b) {
	if (std::numeric_limits<int>::max() - b > a) {
		throw std::overflow_error("more then return can handle");
	}
	return a + b;
}

int main() {
	// Блок кода, который может работать некорректно
	//try {
	//	int a{ 5 }, b{ 0 };
	//	int c{};
	//	if (!b) throw -1; // Событие, вызывающее исключительную ситуацию
	//	// Код, следующий за throw, в случае исключительной ситуации не выполняется
	//	c = a / b;
	//}
	//// Блок, который ловит исключение
	//catch (int ex) {
	//	if (ex == -1) {
	//		printf("devide by 0\n");
	//	}
	//}
	//// Любые исключения, которые кидаются изнутри программы, если они не обработаны cathc-блоками
	//catch (...) { 
	//	printf("Something go wrong\n");
	//}

	::srand(::time(NULL));
	try {
		int i{};
		i = rand() % 2;
		//F00(i);
		Summ(2e30, 4e31);
	}
	catch (std::exception& ex) {
		std::cerr << ex.what() << '\n'; // Метод для вывода сопроводительного текста, находящегося в класса ошибки
	}
	// Универсальный обработчик исключений пишем последним для отолова того, что не поймали предыдущие catch
	catch (...) { 
		printf("Something go wrong\n");
	}

	return 0;
}