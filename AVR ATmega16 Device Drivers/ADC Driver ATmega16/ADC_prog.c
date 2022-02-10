#include "ADC_int.h"

#if ADC_BITS == ADC_BITS_10BIT
static U16 ADC_Result = 0;
#elif ADC_BITS == ADC_BITS_8BIT
static U8 ADC_Result = 0;
#endif
void (*ptr_AdcInt)(void);
void ADC_Init(void){

#if ADC_MODE == ADC_MODE_SINGLE
	ClearBit(ADCSRA,5);
#elif (ADC_MODE == ADC_MODE_AUTOTRIGGER && ADC_AUTOTRIGGERSOURCE == ADC_AUTOTRIGGERSOURCE_TMR0CMP)
	setbit(ADCSRA,5);
	SFIOR = (SFIOR & (~0xE0)) | (ADC_AUTOTRIGGERSOURCE_TMR0CMP << 5);
	setbit(ADCSRA,3);
#endif

	switch(ADC_PRESCALAR){
	case ADC_PRESCALAR_2:
		ADCSRA = (ADCSRA & (~0x07)) | (1 << 0);
		break;
	case ADC_PRESCALAR_4:
		ADCSRA = (ADCSRA & (~0x07)) | (2 << 0);
		break;
	case ADC_PRESCALAR_8:
		ADCSRA = (ADCSRA & (~0x07)) | (3 << 0);
		break;
	case ADC_PRESCALAR_16:
		ADCSRA = (ADCSRA & (~0x07)) | (4 << 0);
		break;
	case ADC_PRESCALAR_32:
		ADCSRA = (ADCSRA & (~0x07)) | (5 << 0);
		break;
	case ADC_PRESCALAR_64:
		ADCSRA = (ADCSRA & (~0x07)) | (6 << 0);
		break;
	case ADC_PRESCALAR_128:
		ADCSRA = (ADCSRA & (~0x07)) | (7 << 0);
		break;
	}

#if ADC_BITS == ADC_BITS_8BIT
	setbit(ADMUX,5);
#elif ADC_BITS == ADC_BITS_10BIT
	clrbit(ADMUX,5);
#endif

#if ADC_REF == ADC_REF_AVCC
	setbit(ADMUX,6);
	clrbit(ADMUX,7);
#elif ADC_REF == ADC_REF_INTERNAL
	setbit(ADMUX,6);
	setbit(ADMUX,7);
#endif

	//Enable ADC
	setbit(ADCSRA,7);

	//Global Interrupts
	//setbit(SREG,7);
}

#if ADC_BITS == ADC_BITS_10BIT
U16 ADC_Read(U8 ADC_CHANNEL_CHx){

	switch(ADC_CHANNEL_CHx){
	case ADC_CHANNEL_CH0:
		ADMUX = (ADMUX & (~0x1F)) | (ADC_CHANNEL_CH0 << 0);
		break;
	case ADC_CHANNEL_CH1:
		ADMUX = (ADMUX & (~0x1F)) | (ADC_CHANNEL_CH1 << 0);
		break;
	case ADC_CHANNEL_CH2:
		ADMUX = (ADMUX & (~0x1F)) | (ADC_CHANNEL_CH2 << 0);
		break;
	case ADC_CHANNEL_CH3:
		ADMUX = (ADMUX & (~0x1F)) | (ADC_CHANNEL_CH3 << 0);
		break;
	case ADC_CHANNEL_CH4:
		ADMUX = (ADMUX & (~0x1F)) | (ADC_CHANNEL_CH4 << 0);
		break;
	case ADC_CHANNEL_CH5:
		ADMUX = (ADMUX & (~0x1F)) | (ADC_CHANNEL_CH5 << 0);
		break;
	case ADC_CHANNEL_CH6:
		ADMUX = (ADMUX & (~0x1F)) | (ADC_CHANNEL_CH6 << 0);
		break;
	case ADC_CHANNEL_CH7:
		ADMUX = (ADMUX & (~0x1F)) | (ADC_CHANNEL_CH7 << 0);
		break;
	}

	setbit(ADCSRA,6);
	#if ADC_AUTOTRIGGERSOURCE == UNINIT
		setbit(ADCSRA,4);
		while(GetBit(ADCSRA,6) == 1);
		return *ptr_g;
	#else
		return 0;
	#endif

}

U16 ADC_GetResult(void){
	return ADC_Result & (0x03FF);
}

#elif ADC_BITS == ADC_BITS_8BIT
void ADC_StartConv(U8 ADC_CHANNEL_CHx){
	switch(ADC_CHANNEL_CHx){
	case ADC_CHANNEL_CH0:
		ADMUX = (ADMUX & (~0x1F)) | (ADC_CHANNEL_CH0 << 0);
		break;
	case ADC_CHANNEL_CH1:
		ADMUX = (ADMUX & (~0x1F)) | (ADC_CHANNEL_CH1 << 0);
		break;
	case ADC_CHANNEL_CH2:
		ADMUX = (ADMUX & (~0x1F)) | (ADC_CHANNEL_CH2 << 0);
		break;
	case ADC_CHANNEL_CH3:
		ADMUX = (ADMUX & (~0x1F)) | (ADC_CHANNEL_CH3 << 0);
		break;
	case ADC_CHANNEL_CH4:
		ADMUX = (ADMUX & (~0x1F)) | (ADC_CHANNEL_CH4 << 0);
		break;
	case ADC_CHANNEL_CH5:
		ADMUX = (ADMUX & (~0x1F)) | (ADC_CHANNEL_CH5 << 0);
		break;
	case ADC_CHANNEL_CH6:
		ADMUX = (ADMUX & (~0x1F)) | (ADC_CHANNEL_CH6 << 0);
		break;
	case ADC_CHANNEL_CH7:
		ADMUX = (ADMUX & (~0x1F)) | (ADC_CHANNEL_CH7 << 0);
		break;
	}
	setbit(ADCSRA,6);

#endif
}

ISR(__vector_14){
	(*ptr_AdcInt)();
}
void Adc_Set_CallBack(void(*Adc_ptr)(void))
{
	ptr_AdcInt = Adc_ptr;
}
