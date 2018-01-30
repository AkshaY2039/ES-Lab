/*
Embedded Systems Lab 4 - 24-01-2018
	Assignment 1.4 : Timer Sub Routines
					In some single threaded embedded system applications, we use timers built using assembler sub-routine.
					This type of routines is sufficient and reasonably accurate for many applications. Develop a 
					sub-routine “Stimer” that can create 1000(approximately)Clock cycles delay. Using this subroutine 
					write another sub-routine “Ltimer” that can create delay which are multiples of 10000 (approximately) 
					cycles. The Ltimer is simple and no need to other timers.The Ltimer can be used to create periodic scan of I/O devices or any periodic activity.
		-- Akshay Kumar	(CED15I031)
*/

/*DATA SECTION*/
	/*labels being used*/