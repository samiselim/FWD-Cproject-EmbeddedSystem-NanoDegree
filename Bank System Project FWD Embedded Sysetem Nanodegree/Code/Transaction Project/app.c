#include "app.h"

void appStart(void)
{
	
	printf(" *********   Welcome To Transaction Bank System   ************** \n");
	
		while (getCardHolderName(&TData.cardHolderData) == WRONG_NAME)
		{
			printf("Wrong Card Holder Name ... \n ");
		}

		while (getCardExpiryDate(&TData.cardHolderData) == WRONG_EXP_DATE)
		{
			printf("Wrong Expired Date ... \n ");
		}

		while (getCardPAN(&TData.cardHolderData) == WRONG_PAN)
		{
			printf("Wrong PAN format ... \n ");
		}
		while (getTransactionDate(&TData.terminalData) == WRONG_DATE)
		{
			printf("wrong date format ... \n ");
		}

		while (getTransactionAmount(&TData.terminalData) == INVALID_AMOUNT)
		{
			printf("Enter Valid Transaction Amount ... \n");
		}
		while (setMaxAmount(&TData.terminalData) == INVALID_MAX_AMOUNT)
		{
			printf("Enter Valid MAX Transaction Amount ... \n");
		}

		
	State = recieveTransactionData(&TData);
	switch (State)
	{
	case APPROVED:
		printf("\nThe Transaction is Approved and Saved Successfully ... \n");
		break;

	case INTERNAL_SERVER_ERROR:
		printf("\nThe Transaction is not Save ! ...  Internal Server Error ... \n");
		break;
	case DECLINED_INSUFFECIENT_FUND:
		printf("\nBalance is not enough  ...  \n");
		break;
	case DECLINED_STOLEN_CARD:
		printf("\nDeclined Invalid Account .. ");
		break;
	case eXPIRED_CARD:
		printf("\nCard is Expired  ... \n");
		break;
	case eXEEDMAXAMOUNT:
		printf("Exceed MAX Transaction Amount ... \n");
		break;
	default:
	
		break;
	
	}
	/*
*/
}
