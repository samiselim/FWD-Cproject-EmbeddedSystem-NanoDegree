#include"card.h"


EN_cardError_t getCardHolderName(ST_cardData_t* cardData) 
{
	uint8_t const str[25];
	uint8_t strL = 0;

	printf("Please Enter CardHolderName ... hint: [  MIN 20 ... MAX 24  ] --> ");
	gets(str);

	if (str[strL] == '\0') return WRONG_NAME;

	while (str[strL] != '\0')
		strL++;

	if (strL >= 20 && strL <= 24)
	{
		for(int i=0 ; i<25 ; i++)
		{
			if (str[i] >= '0' && str[i] <= '9')return WRONG_NAME;
			cardData->cardHolderName[i] = str[i];
		}
		printf("Successfull Card Holder Name . . . \n");
		return OK;
	}
	
	else return  WRONG_NAME;
}


EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) 
{
	printf("Please Enter Card Expire Date --> in format hint : [MM/YY]   -->  ");
	uint8_t const str[20];
	uint8_t strL = 0;
	gets(str);
	while (str[strL] != '\0')
		strL++;
	
	unsigned pow1 = 10;
	
	while ((int)str[0] >= pow1)
		pow1 *= 10;

	/*02/22  -- >>   (int)0 = 48  (int)2 = 50    -->  (4850) */
	/* 4950    12  */
	if(strL != 5)
	{
		return WRONG_EXP_DATE;
	}
		
	/* 01/22 */
	if (str[2] != '/') return WRONG_EXP_DATE;
	else if (str[0] * pow1 +str[1] > 4950) return WRONG_EXP_DATE;
	
	else
	{
		for (int i = 0; i < 5; i++)
		{
			if (i == 2) continue;
			if (!isdigit(str[i])) return WRONG_EXP_DATE;
		}

		for (int i = 0; i < 6; i++)
		{
			cardData->cardExpirationDate[i] = str[i];
		}
		printf("Successfull Expired Date . . . \n");
		return OK;
	}
}


EN_cardError_t getCardPAN(ST_cardData_t* cardData) 
{

	printf("Please Enter Primary Account Number --> hint: 20 charcters  ... ");
	uint8_t const str[30];
	uint8_t strL = 0 , numCount=0;
	gets(str);
	while (str[strL] != '\0')
		strL++;

	if (strL < 16 && strL >19)
	{
		return WRONG_PAN;
	}
	else
	{
		for (int i = 0; i < strL;i++)
		{
			if (!isdigit(str[i])) return WRONG_PAN;			
		}

			for (int i = 0; i < 20; i++)
			{
				cardData->primaryAccountNumber[i] = str[i];
			}
			printf("Valid PAN  . . . \n");
			return OK;
	}
	

}
