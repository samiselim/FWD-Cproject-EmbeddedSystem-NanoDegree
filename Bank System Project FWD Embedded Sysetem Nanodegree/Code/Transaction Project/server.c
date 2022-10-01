#include"server.h"

ST_accountsDB_t VaildDataBase[255] = { {1000.0 ,"12345678912345678"} , {100000.0 , "2345678912345678912"} , {50000.0, "8989374615436851" } , {20000.0, "9989374615436851" } , {70000.0, "9999374615436851"} };
ST_transaction_t TransDataBase[255] = { [0].transactionSequenceNumber = 1,[1].transactionSequenceNumber=2 ,[2].transactionSequenceNumber = 3 };
uint16_t seqTNumber = 3;
 
EN_transStat_t recieveTransactionData(ST_transaction_t* transData)
{
	
	if (isValidAccount(&transData->cardHolderData) != ACCOUNT_NOT_FOUND)
	{
		if (isBelowMaxAmount(&transData->terminalData) == EXCEED_MAX_AMOUNT) 
		{
			return eXEEDMAXAMOUNT;
		}
	
		if(isCardExpired(transData->cardHolderData, transData->terminalData) == EXPIRED_CARD)
		{
			return eXPIRED_CARD;
		}

		if (saveTransaction(transData) == SAVING_FAILED)
			return transData->transState = INTERNAL_SERVER_ERROR;
		
		else if (isAmountAvailable(transData) == __OK)
		{
				uint8_t	account_num = isValidAccount(&transData->cardHolderData);
				VaildDataBase[account_num].balance -= transData->terminalData.transAmount;
				printf("Balance is Updated succsessfully ... \nNew Balance is :  %0.2f" , VaildDataBase[account_num].balance);

		
				TransDataBase[seqTNumber-1].transState = transData->transState = APPROVED;
				return APPROVED;	
		}
		else 
		{
				TransDataBase[seqTNumber-1].transState = transData->transState = DECLINED_INSUFFECIENT_FUND;
				return DECLINED_INSUFFECIENT_FUND;
			
		}

	}

	return transData->transState = DECLINED_STOLEN_CARD;
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData) 
{
	for (int j = 0; j < 255; j++) 
	{
			if(strcmp(cardData->primaryAccountNumber , VaildDataBase[j].primaryAccountNumber) == 0)
			{
				return j;
			}
			else
			{
				/*
				
				*/
			}	
	}
	return ACCOUNT_NOT_FOUND;
	
}
EN_serverError_t isAmountAvailable(ST_transaction_t* transData)
{
        uint8_t	account_num = isValidAccount(&transData->cardHolderData);
		if (transData->terminalData.transAmount <= VaildDataBase[account_num].balance)
		{
			return __OK;
		}
		else
		{
			return LOW_BALANCE;
		}
}

EN_serverError_t saveTransaction(ST_transaction_t* transData) 
{
	if(seqTNumber == 255) return SAVING_FAILED;
	seqTNumber++;
	TransDataBase[seqTNumber] = *transData;
	return __OK;
}

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
{
	for (uint16_t i = 0; i < seqTNumber; i++)
	{
		if (TransDataBase[i].transactionSequenceNumber == transactionSequenceNumber)
		{
			transData = &TransDataBase[i];
			return __OK;
		}

	}
	return TRANSACTION_NOT_FOUND;

}