/*
 * myTask.c
 *
 *  Created on: Nov 24, 2019
 *      Author: Umroh Tul Khasanah
 *
 */

#include <LCDku.h>
#include <Taskku.h>

/* ------------------------------- */
enum flag{tdkKoin, masuk500, masuk1000}Flagku;
enum state{start, startDelay, coin1, coin2, siap, drop, batal, k500, k1000}stateku;
volatile uint16_t delay=0;
volatile uint16_t debounce1=0xFF;
volatile uint16_t debounce2=0xFF;
volatile uint16_t debounce3=0xFF;
volatile uint16_t debounce4=0xFF;
volatile uint16_t uang=0;

void Task_init(void){
	myLCD_init();
	myLCD_clear();
	ledDrop(0);
	led500(0);
	led1000(0);
}

Task_run(){
	switch(stateku){
	case start:{
		myLCD_setCursor(0, 0); myLCD_print("Vending Machine");
		myLCD_setCursor(0, 1); myLCD_print("Umroh Tul Khasanah");
		myLCD_setCursor(0, 2); myLCD_print("1110171037");
		myLCD_setCursor(0, 3); myLCD_print("3D4 Elektronika B");
		stateku=startDelay;

	}break;

	case startDelay:{
		if(++delay > 1000){		//2mS * 1000
			delay=0;
			myLCD_clear();
			myLCD_setCursor(0, 0); myLCD_print("Masukkan koin !");
			myLCD_setCursor(0, 1); myLCD_print("Harga permen Rp.1000");
			stateku=coin1;
		}

	}break;

	case coin1:{
		myLCD_setCursor(0, 3); myLCD_print("Uang: Rp."); myLCD_printNum(uang);
		if(PB_500()){
			myLCD_clear();
			myLCD_setCursor(0, 0); myLCD_print("Rp.500");
			myLCD_setCursor(0, 1); myLCD_print("Berhasil Dimasukkan!");
			buzzer(1);
			Flagku=masuk500;
		}

		if(Flagku==masuk500){
			if(++delay > 80){
				delay=0;
				uang = uang + 500;
				buzzer(0);
				myLCD_clear();
				myLCD_setCursor(0, 0); myLCD_print("Masukkan koin !");
				myLCD_setCursor(0, 1); myLCD_print("Harga permen Rp.1000");
				Flagku=tdkKoin;
				stateku=coin2;
			}
		}
		if(PB_1000()){
			myLCD_clear();
			myLCD_setCursor(0, 0); myLCD_print("Rp.1000");
			myLCD_setCursor(0, 1); myLCD_print("Berhasil Dimasukkan!");
			buzzer(1);
			Flagku=masuk1000;
		}

		if(Flagku==masuk1000){
			if(++delay > 80){
				delay=0;
				uang = uang + 1000;
				buzzer(0);
				myLCD_clear();
				Flagku=tdkKoin;
				myLCD_setCursor(0, 0); myLCD_print("Yakin Beli ?");
				myLCD_setCursor(0, 1); myLCD_print("[Proses/Batal]");
				myLCD_setCursor(0, 3); myLCD_print("Uang: Rp."); myLCD_printNum(uang);
				stateku=siap;
			}
		}

	}break;

	case coin2:{
		myLCD_setCursor(0, 3); myLCD_print("Uang: Rp."); myLCD_printNum(uang);
		if(PB_500()){
			myLCD_clear();
			myLCD_setCursor(0, 0); myLCD_print("Rp.500");
			myLCD_setCursor(0, 1); myLCD_print("Berhasil Dimasukkan!");
			buzzer(1);
			Flagku=masuk500;
		}

		if(Flagku==masuk500){
			if(++delay > 80){
				delay=0;
				uang = uang + 500;
				buzzer(0);
				myLCD_clear();
				Flagku=tdkKoin;
				myLCD_setCursor(0, 0); myLCD_print("Yakin Beli ?");
				myLCD_setCursor(0, 1); myLCD_print("[Proses/Batal]");
				myLCD_setCursor(0, 3); myLCD_print("Uang: Rp."); myLCD_printNum(uang);
				stateku=siap;
			}
		}

		if(PB_1000()){
			myLCD_clear();
			myLCD_setCursor(0, 0); myLCD_print("Rp.1000");
			myLCD_setCursor(0, 1); myLCD_print("Berhasil Dimasukkan!");
			buzzer(1);
			Flagku=masuk1000;
		}

		if(Flagku==masuk1000){
			if(++delay > 80){
				delay=0;
				uang = uang + 1000;
				buzzer(0);
				myLCD_clear();
				Flagku=tdkKoin;
//				myLCD_setCursor(0, 0); myLCD_print("Yakin Beli ?");
//				myLCD_setCursor(0, 1); myLCD_print("[Proses/Batal]");
				myLCD_setCursor(0, 3); myLCD_print("Uang: Rp."); myLCD_printNum(uang);
				stateku=k500;
			}
		}


		if(PB_Cancel()){
			myLCD_clear();
			stateku=batal;
		}

	}break;

	case siap:{
		if(PB_Process()){
			uang = uang - 1000; 	//uang diambil untuk beli permen
			myLCD_clear();
			stateku=drop;
		}
		if(PB_Cancel()){
			myLCD_clear();
			stateku=batal;
		}
		if(PB_500()){
			uang = uang + 500; 	//masuk 500 lagi
			myLCD_clear();
			stateku=k500;
		}
		if(PB_1000()){
			uang = uang + 1000; //masuk 1000 lagi
			myLCD_clear();
			stateku=k1000;
		}

	}break;

	case drop:{
		myLCD_setCursor(0, 0); myLCD_print("Pembelian berhasil");
		myLCD_setCursor(0, 1); myLCD_print("Terimakasih !");
		ledDrop(1);
		buzzer(1);
		if(++delay > 80){
			delay=0;
			buzzer(0);
			myLCD_clear();
			ledDrop(0);
			stateku=start;
		}
	}break;

	case batal:{
		if(uang == 1000){
			led1000(1);
			buzzer(1);
			myLCD_setCursor(0, 0); myLCD_print("Pembelian dibatalkan");
			myLCD_setCursor(0, 1); myLCD_print("Rp.1000");
			myLCD_setCursor(0, 2); myLCD_print("Dikembalikan !");
			if(++delay > 30){
				uang = uang - 1000; //uang dikembalikan 1000
				delay=0;
				led1000(0);
				buzzer(0);
				stateku = start;
			}
		}

		if(uang == 500){
			led500(1);
			buzzer(1);
			myLCD_setCursor(0, 0); myLCD_print("Pembelian dibatalkan");
			myLCD_setCursor(0, 1); myLCD_print("Rp.500");
			myLCD_setCursor(0, 2); myLCD_print("Dikembalikan !");
			if(++delay > 30){
				uang = uang - 500; //uang dikembalikan 1000
				delay=0;
				led500(0);
				buzzer(0);
				stateku = start;
			}
		}
	}break;

	case k500:{
		led500(1);
		buzzer(1);
		myLCD_setCursor(0, 0); myLCD_print("Uang lebih !");
		myLCD_setCursor(0, 1); myLCD_print("Rp.500");
		myLCD_setCursor(0, 2); myLCD_print("Dikembalikan !");
		if(++delay > 30){
			uang = uang - 500; //uang dikembalikan 500
			delay=0;
			led500(0);
			buzzer(0);
			myLCD_clear();
			myLCD_setCursor(0, 0); myLCD_print("Yakin Beli ?");
			myLCD_setCursor(0, 1); myLCD_print("[Proses/Batal]");
			myLCD_setCursor(0, 3); myLCD_print("Uang: Rp."); myLCD_printNum(uang);
			stateku = siap;
		}

	}break;

	case k1000:{
		led1000(1);
		buzzer(1);
		myLCD_setCursor(0, 0); myLCD_print("Uang lebih !");
		myLCD_setCursor(0, 1); myLCD_print("Rp.1000");
		myLCD_setCursor(0, 2); myLCD_print("Dikembalikan !");
		if(++delay > 30){
			uang = uang - 1000; //uang dikembalikan 500
			delay=0;
			led1000(0);
			buzzer(0);
			myLCD_clear();
			myLCD_setCursor(0, 0); myLCD_print("Yakin Beli ?");
			myLCD_setCursor(0, 1); myLCD_print("[Proses/Batal]");
			myLCD_setCursor(0, 3); myLCD_print("Uang: Rp."); myLCD_printNum(uang);
			stateku = siap;
		}
	}break;
	}
}

/* ---------------------------------------------------------------------------------------- */
_Bool PB_Process(void){
	_Bool flagDetect=0;
	if(HAL_GPIO_ReadPin(PB_PROCESS_GPIO_Port, PB_PROCESS_Pin)==0)
		debounce1 = debounce1<<1;
	else
		debounce1 = (debounce1<<1)|1;
	if(debounce1==3)
		flagDetect=1;
	return flagDetect;
}

_Bool PB_Cancel(void){
	_Bool flagDetect=0;
	if(HAL_GPIO_ReadPin(PB_CANCEL_GPIO_Port, PB_CANCEL_Pin)==0)
		debounce2 = debounce2<<1;
	else
		debounce2 = (debounce2<<1)|1;
	if(debounce2==3)
		flagDetect=1;
	return flagDetect;
}

_Bool PB_500(void){
	_Bool flagDetect=0;
	if(HAL_GPIO_ReadPin(PB_500_GPIO_Port, PB_500_Pin)==0)
		debounce3 = debounce3<<1;
	else
		debounce3 = (debounce3<<1)|1;
	if(debounce3==3)
		flagDetect=1;
	return flagDetect;
}

_Bool PB_1000(void){
	_Bool flagDetect=0;
	if(HAL_GPIO_ReadPin(PB_1000_GPIO_Port, PB_1000_Pin)==0)
		debounce4 = debounce4<<1;
	else
		debounce4 = (debounce4<<1)|1;
	if(debounce4==3)
		flagDetect=1;
	return flagDetect;
}


