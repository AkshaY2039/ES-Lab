mov r0,#0x02;				
swi 0x201 @ left LED on;	
mov r0,#0x01;				
swi 0x201 @ right LED on;	
mov r0,#0x03;				
swi 0x201 @ both LEDs on;	
swi 0x11;					exit