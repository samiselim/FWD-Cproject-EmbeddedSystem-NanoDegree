#include"terminal.h"


EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	uint8_t Dat[11], DatL = 0;
	printf("Please Enter Transaction Date -- hint: format [DD:MM:YYYY] -->  ");
	gets(Dat);
	
	unsigned pow1 = 10;
	unsigned pow2 = 10;

	while ((int)Dat[0] >= pow1)
		pow1 *= 10;

	while ((int)Dat[3] >= pow2)
		pow2 *= 10;

	
	
	while (Dat[DatL] != '\0')
		DatL++;

	if (DatL != 10) return WRONG_DATE;
	else
	{
		if (Dat[2] != ':' && Dat[5] != ':') return WRONG_DATE;
		else 
		{
				for (int i = 0; i < 10; i++)
				{
					if (i == 2 || i == 5) continue;
					if (!isdigit(Dat[i])) return WRONG_DATE;
				}
				if (Dat[0] * pow1 + Dat[1] > 5149) return WRONG_DATE; //31 
				else if (Dat[3] * pow2 + Dat[4] > 4950) return WRONG_DATE; //12
				else
				{
					for (int i = 0; i < 10; i++)
					{
						termData->transactionDate[i] = Dat[i];
					}
					return _OK;
				}
		}
	}

}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	if (cardData.cardExpirationDate[3] > termData.transactionDate[8])
	{
		return _OK;
	}
	else if (cardData.cardExpirationDate[3] < termData.transactionDate[8])return EXPIRED_CARD;
	else
	{
		if (cardData.cardExpirationDate[4] > termData.transactionDate[9]) 
		{
			
			return _OK;
		}
		else if (cardData.cardExpirationDate[4] < termData.transactionDate[9])return EXPIRED_CARD;
		else
		{
			if (cardData.cardExpirationDate[0] > termData.transactionDate[3]) 
			{
				
				return _OK;
			}
			else if (cardData.cardExpirationDate[0] < termData.transactionDate[3])return EXPIRED_CARD;
			else
			{
				if (cardData.cardExpirationDate[1] > termData.transactionDate[4]) 
				{
					
					return _OK;
				}
				else return EXPIRED_CARD;
			}
		}
	}
}
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{
	if (getCardPAN(cardData) == OK) 
	{
		return _OK;
	}else if(getCardPAN(cardData) == WRONG_PAN)
	{
		return INVALID_CARD;
	}
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) 
{
	
	printf("Please Enter Transaction Amount ...  hint: [More Than Zero] -->:   ");
	scanf("%f", &termData->transAmount);

	if (termData->transAmount <= 0) return INVALID_AMOUNT;
	else 
	{
		return OK;
	} 
	
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if (termData->transAmount > termData->maxTransAmount)return EXCEED_MAX_AMOUNT;
	else 
	{
		return _OK;
	}
}


EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	printf("Please Enter Terminal MAX Amount hint: Max Amount greater than  0 -- >   ");
	
	scanf("%f", &termData->maxTransAmount);

	if (termData->maxTransAmount <= 0)return INVALID_MAX_AMOUNT;
	else return _OK;

}
