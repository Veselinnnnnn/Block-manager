#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct blockInfo{
    int floors;
    int apartmentsPerFloor;
    struct ApartmentInfo **apartment;
}*BlockID;

struct ApartmentInfo{
    int apartmentNumber;
    int numberOfRooms;
    int numberOfAdults;
    int numberOfChildren;
    char apartmentHolders[15];
    char dateOfAccommodation[10];
    int rent;
};

void FloorsAndApartments(int blockIDNumber){
    printf("Floors: ");
    scanf("%d", &BlockID[blockIDNumber].floors);

    printf("Apartments per Floor: ");
    scanf("%d", &BlockID[blockIDNumber].apartmentsPerFloor);
}

void closeTheProgram(FILE *fp,int *numbersOfBlocks){
    for(int i=0; i < (*numbersOfBlocks);i++){
        if(checkingFileExistence(fp,i)==1){
            for(int j=0;j<BlockID[i].floors;j++){
                free(BlockID[i].apartment[j]);
            }
        }
    }

    free(BlockID);

    printf("Good Bye! :)");
    exit(0);
}

void allocatingMemoryOfOneBlock(int blockIDNumber){

    BlockID[blockIDNumber].apartment= (struct ApartmentInfo **) malloc(BlockID[blockIDNumber].floors * sizeof(struct ApartmentInfo*));
    if(BlockID[blockIDNumber].apartment == NULL){
        printf("Out of memory for floors!\n");
        exit(1);
    }

    for (int i = 0; i < BlockID[blockIDNumber].floors; i++) {
        BlockID[blockIDNumber].apartment[i] = (struct ApartmentInfo *) malloc(BlockID[blockIDNumber].apartmentsPerFloor * sizeof(struct ApartmentInfo));
        if ( BlockID[blockIDNumber].apartment[i]==NULL){
            printf("Out of memory for apartments per floor!\n");
            exit(1);
        }
    }
}

void freeAllApartments(int blockIDNumber){

    int counter=1;
    for(int i=0;i<BlockID[blockIDNumber].floors;i++){
        for(int j=0; j<BlockID[blockIDNumber].apartmentsPerFloor;j++){
            if(j==2){
                BlockID[blockIDNumber].apartment[i][j].apartmentNumber=counter;
                BlockID[blockIDNumber].apartment[i][j].numberOfRooms=3;
                BlockID[blockIDNumber].apartment[i][j].numberOfAdults=0;
                BlockID[blockIDNumber].apartment[i][j].numberOfChildren=0;
                strcpy(BlockID[blockIDNumber].apartment[i][j].apartmentHolders,"none");
                strcpy(BlockID[blockIDNumber].apartment[i][j].dateOfAccommodation,"none");
                BlockID[blockIDNumber].apartment[i][j].rent=0;
                counter++;
            }else{
                BlockID[blockIDNumber].apartment[i][j].apartmentNumber=counter;
                BlockID[blockIDNumber].apartment[i][j].numberOfRooms=2;
                BlockID[blockIDNumber].apartment[i][j].numberOfAdults=0;
                BlockID[blockIDNumber].apartment[i][j].numberOfChildren=0;
                strcpy(BlockID[blockIDNumber].apartment[i][j].apartmentHolders,"none");
                strcpy(BlockID[blockIDNumber].apartment[i][j].dateOfAccommodation,"none");
                BlockID[blockIDNumber].apartment[i][j].rent=0;
                counter++;
            }
        }
    }
}

int checkingFileExistence(FILE *fp, int blockIDNumber){
    char filename[32];
    sprintf (filename, "file%d.bin", blockIDNumber);

    if((fp = fopen(filename, "rb"))==NULL){
        return 0;
    }
    return 1;
}

void reWritingTheBinaryFile(FILE *fp,int *blockIDNumber){

    char filename[32];
    sprintf (filename, "file%d.bin", *blockIDNumber);

    if((fp = fopen(filename, "wb"))==NULL){
        printf("Cannot open file. \n");
        exit(1);
    }

    if(fwrite(&BlockID[*blockIDNumber].floors, sizeof(BlockID[*blockIDNumber].floors), 1, fp) != 1){
        printf("Write error occurred for floors. \n");
        exit(1);
    }

    if(fwrite(&BlockID[*blockIDNumber].apartmentsPerFloor, sizeof(BlockID[*blockIDNumber].apartmentsPerFloor), 1, fp) != 1){
        printf("Write error occurred for apartments. \n");
        exit(1);
    }

    for(int i=0;i<BlockID[*blockIDNumber].floors;i++){
        for(int j=0;j<BlockID[*blockIDNumber].apartmentsPerFloor;j++){
            if(BlockID[*blockIDNumber].apartment[i][j].numberOfAdults!=0){
                if(fwrite(&BlockID[*blockIDNumber].apartment[i][j].apartmentNumber, sizeof(BlockID[*blockIDNumber].apartment[i][j].apartmentNumber), 1, fp) != 1){
                    printf("Error: writing in file after adding apartmentNumber! \n");
                    exit(1);
                }
                if(fwrite(&BlockID[*blockIDNumber].apartment[i][j].numberOfRooms, sizeof(BlockID[*blockIDNumber].apartment[i][j].numberOfRooms), 1, fp) != 1){
                    printf("Error: writing in file after adding numbers of rooms! \n");
                    exit(1);
                }
                if(fwrite(&BlockID[*blockIDNumber].apartment[i][j].numberOfAdults, sizeof(BlockID[*blockIDNumber].apartment[i][j].numberOfAdults), 1, fp) != 1){
                    printf("Error: writing in file after adding numbers of adults! \n");
                    exit(1);
                }
                if(fwrite(&BlockID[*blockIDNumber].apartment[i][j].numberOfChildren, sizeof(BlockID[*blockIDNumber].apartment[i][j].numberOfChildren), 1, fp) != 1){
                    printf("Error: writing in file after adding numbers of children! \n");
                    exit(1);
                }
                if(fwrite(&BlockID[*blockIDNumber].apartment[i][j].rent, sizeof(BlockID[*blockIDNumber].apartment[i][j].rent), 1, fp) != 1){
                    printf("Error: writing in file after adding rent! \n");
                    exit(1);
                }
            }
        }
    }

    fclose(fp);
}

void readingTheFileAndFillTheArray(FILE *fp,int blockIDNumber){
    char filename[32];
    int temp=0;
    int apartmentNumber;

    sprintf (filename, "file%d.bin", blockIDNumber);

    if((fp = fopen(filename, "rb"))==NULL){
        printf("Cannot open file to read. \n");
        exit(1);
    }

    if(fread(&BlockID[blockIDNumber].floors,sizeof(BlockID[blockIDNumber].floors),1,fp)!=1){
        printf("Error reading floors.");
        exit(1);
    }

    if(fread(&BlockID[blockIDNumber].apartmentsPerFloor,sizeof(BlockID[blockIDNumber].apartmentsPerFloor),1,fp)!=1){
        printf("Error reading apartments per floor.");
        exit(1);
    }

    printf("Floors: %d \t Apartments: %d", BlockID[blockIDNumber].floors,BlockID[blockIDNumber].apartmentsPerFloor);

    allocatingMemoryOfOneBlock(blockIDNumber);

    freeAllApartments(blockIDNumber);

    for(int i=0; i< BlockID[blockIDNumber].floors; i++){
        for(int j=0;j<BlockID[blockIDNumber].apartmentsPerFloor;j++){
            if(temp==0){
                if(fread(&apartmentNumber, sizeof(apartmentNumber),1,fp)==1){
                    temp=1;
                }
            }

            if(BlockID[blockIDNumber].apartment[i][j].apartmentNumber==apartmentNumber){
                if(fread(&BlockID[blockIDNumber].apartment[i][j].numberOfRooms, sizeof(BlockID[blockIDNumber].apartment[i][j].numberOfRooms),1,fp)!=1){
                    printf("Error reading number of rooms.");
                    exit(1);
                }

                if(fread(&BlockID[blockIDNumber].apartment[i][j].numberOfAdults, sizeof(BlockID[blockIDNumber].apartment[i][j].numberOfAdults),1,fp)!=1){
                    printf("Error reading number of adults.");
                    exit(1);
                }

                if(fread(&BlockID[blockIDNumber].apartment[i][j].numberOfChildren, sizeof(BlockID[blockIDNumber].apartment[i][j].numberOfChildren),1,fp)!=1){
                    printf("Error reading number of children.");
                    exit(1);
                }

                if(fread(&BlockID[blockIDNumber].apartment[i][j].rent, sizeof(BlockID[blockIDNumber].apartment[i][j].rent),1,fp)!=1){
                    printf("Error reading rent.");
                    exit(1);
                }

                temp=0;
            }
        }
    }


    fclose(fp);
}

void entraceFeeChecking(int *blockIDNumber){
    int floor;
    int apartmentN;
    int apartmentValidationStart;
    int apartmentValidationEnd;
    int price;
    int floorC;
    int apartmentC;

    do{

        printf("On which floor is the apartment you want to check: ");
        scanf("%d", &floor);
        fflush(stdin);

        if(floor<0 || floor>BlockID[*blockIDNumber].floors){
            printf("There is no such floor! Try Again!\n");
        }
    }while(floor<0 || floor>BlockID[*blockIDNumber].floors);


    apartmentValidationStart=((floor-1)*BlockID[*blockIDNumber].apartmentsPerFloor)+1;
    apartmentValidationEnd=floor*BlockID[*blockIDNumber].apartmentsPerFloor;

    printf("\nThere is %d apartments --> %d", BlockID[*blockIDNumber].apartmentsPerFloor,apartmentValidationStart);

    for(int i=1;i<BlockID[*blockIDNumber].apartmentsPerFloor;i++){
        printf(", %d", apartmentValidationStart+i);
    }
    printf("\n\n");
    do{

        printf("The apartment you want to check: ");
        scanf("%d", &apartmentN);
        fflush(stdin);

        if(apartmentN<apartmentValidationStart || apartmentN>apartmentValidationEnd){
            printf("There is no such apartment! Try Again!\n");
        }
    }while(apartmentN<apartmentValidationStart|| apartmentN>apartmentValidationEnd);

    floorC= floor-1;

    if(apartmentN%BlockID[*blockIDNumber].apartmentsPerFloor!=0){
        apartmentC=(apartmentN%BlockID[*blockIDNumber].apartmentsPerFloor)-1;
    }else{
        apartmentC=BlockID[*blockIDNumber].apartmentsPerFloor-1;
    }

    if(BlockID[*blockIDNumber].apartment[floorC][apartmentC].numberOfAdults==0){
        printf("There are no people accommodated here!\n");
    }else{
        price=entranceFee(floorC,apartmentC,*blockIDNumber);
        printf("Entrance fee: %d\n",price);
    }
}

int entranceFee(int floorN,int apartmentN,int blockIDNumber){
    int fee;

    if(floorN== 0 || floorN==1){
        fee=(BlockID[blockIDNumber].apartment[floorN][apartmentN].numberOfAdults*3)+(BlockID[blockIDNumber].apartment[floorN][apartmentN].numberOfChildren*1);
    }else{
        fee=(BlockID[blockIDNumber].apartment[floorN][apartmentN].numberOfAdults*5)+(BlockID[blockIDNumber].apartment[floorN][apartmentN].numberOfChildren*3);
    }

    return fee;
}

int rentCalculating(int floor, int apartmentNumber, int blockIDNumber){
    if(BlockID[blockIDNumber].apartment[floor][apartmentNumber].numberOfRooms==3){
        BlockID[blockIDNumber].apartment[floor][apartmentNumber].rent=400;
    }else{
        BlockID[blockIDNumber].apartment[floor][apartmentNumber].rent=300;
    }
    return BlockID[blockIDNumber].apartment[floor][apartmentNumber].rent;
}

void accommodationOfPeopleNew(int *flag, FILE *fp, int *blockIDNumber){
    int apartmentValidationStart;
    int apartmentValidationEnd;
    int floor;
    int apartmentN;
    int apartmentC;
    int floorC;
    char ch;

    do{
        printf("\nOn which floor you are looking to stay?\n");
        scanf("%d",&floor);
        if(floor<=0 || floor>BlockID[*blockIDNumber].floors){
            if(floor==0){
                printf("\nYou cannot stay in the lobby!\n");
            }else{
                printf("\nThere is no such floor! Try Again!\n");
            }
        }
    }while(floor<=0 || floor>BlockID[*blockIDNumber].floors);

    apartmentValidationStart=((floor-1)*BlockID[*blockIDNumber].apartmentsPerFloor)+1;
    apartmentValidationEnd=floor*BlockID[*blockIDNumber].apartmentsPerFloor;

    do{
        do{
            printf("\nThere is %d apartments --> %d", BlockID[*blockIDNumber].apartmentsPerFloor,apartmentValidationStart);
            for(int i=1;i<BlockID[*blockIDNumber].apartmentsPerFloor;i++){
                printf(", %d", apartmentValidationStart+i);
            }

            printf("\nChoose one of them: ");
            scanf("%d", &apartmentN);

            if(apartmentN < apartmentValidationStart || apartmentN > apartmentValidationEnd){
                printf("There is no such apartment! Try Again!\n");
            }
        }while(apartmentN < apartmentValidationStart || apartmentN > apartmentValidationEnd);

        if(apartmentN%BlockID[*blockIDNumber].apartmentsPerFloor!=0){
            apartmentC=(apartmentN%BlockID[*blockIDNumber].apartmentsPerFloor)-1;
        }else{
            apartmentC=BlockID[*blockIDNumber].apartmentsPerFloor-1;
        }

        floorC=floor-1;

        if(BlockID[*blockIDNumber].apartment[floorC][apartmentC].numberOfAdults==0){
            printf("\nThe apartment is free! You can stay! \n");
            ch='s';
            printf("How many adults are going to stay?\n");

            do{
                scanf("%d",&BlockID[*blockIDNumber].apartment[floorC][apartmentC].numberOfAdults);
                if(BlockID[*blockIDNumber].apartment[floorC][apartmentC].numberOfAdults == 0 || BlockID[*blockIDNumber].apartment[floorC][apartmentC].numberOfAdults<0){
                    printf("You can stay if there is at least 1 adults!\n");
                }else{
                    printf("How many children will be accommodated with you?\n");

                    do{
                        scanf("%d",&BlockID[*blockIDNumber].apartment[floorC][apartmentC].numberOfChildren);
                        fflush(stdin);
                        if(BlockID[*blockIDNumber].apartment[floorC][apartmentC].numberOfChildren<0){
                            printf("There can be no negative child!\n");
                        }else{
                            printf("What is your family?\n");
                            gets(BlockID[*blockIDNumber].apartment[floorC][apartmentC].apartmentHolders);

                            printf("Date of accommodation: ");
                            gets(BlockID[*blockIDNumber].apartment[floorC][apartmentC].dateOfAccommodation);

                            printf("\nCongrats, %s! Welcome to your new home!\n",BlockID[*blockIDNumber].apartment[floorC][apartmentC].apartmentHolders);
                            printf("Your rent is: %d lv.", rentCalculating(floorC,apartmentC,*blockIDNumber));
                            printf("\nMake sure to pay your rent on time!\n");
                            printf("Your entrance fee is: %d lv.", entranceFee(floorC,apartmentC,*blockIDNumber));
                            printf("\nMake sure not to forget it!\n");
                            (*flag)++;
                            reWritingTheBinaryFile(fp,blockIDNumber);
                            }

                    }while(BlockID[*blockIDNumber].apartment[floorC][apartmentC].numberOfChildren<0);
                }
            }while(BlockID[*blockIDNumber].apartment[floorC][apartmentC].numberOfAdults == 0 || BlockID[*blockIDNumber].apartment[floorC][apartmentC].numberOfAdults<0);
        }else{
            printf("\nThe apartment is not free! If you want you can choose another apartment!\n");
            printf("Do you want to choose again ?(y/n)\n");

            do{
                ch = getchar();
                fflush(stdin);
                if(ch=='y' || ch=='n'){
                    if(ch!='y' || ch!='n'){
                        printf("Please answer with 'y' or 'n'!\n");
                    }
                    break;
                }
            }while(ch!='y' || ch!='n');
        }
    }while(ch=='y');
}

void addOneMoreBlock( int *numbersOfBlocks){

    (*numbersOfBlocks)++;

    BlockID = (struct blockInfo *) realloc(BlockID,*numbersOfBlocks);

}

void releaseOfTheApartment(int *flag, FILE *fp, int *blockIDNumber){

    int apartmentNumberToRelease;
    int apartmentFloorToRelease;
    int apartmentC;

    if((*flag)>0){
        printf("Which apartment do you want to release?\n");
            do{
                scanf("%d", &apartmentNumberToRelease);
                fflush(stdin);
                if(apartmentNumberToRelease>(BlockID[*blockIDNumber].floors*BlockID[*blockIDNumber].apartmentsPerFloor) || apartmentNumberToRelease<1){
                    printf("There is no such apartment! Try Again!");
                }else{
                    printf("\nOn which floor is this apartment? \n");
                    scanf("%d",&apartmentFloorToRelease);
                    fflush(stdin);

                    apartmentFloorToRelease-=1;

                    if(apartmentNumberToRelease%BlockID[*blockIDNumber].apartmentsPerFloor!=0){
                        apartmentC=(apartmentNumberToRelease%BlockID[*blockIDNumber].apartmentsPerFloor)-1;
                    }else{
                        apartmentC=BlockID[*blockIDNumber].apartmentsPerFloor-1;
                    }
                    if(BlockID[*blockIDNumber].apartment[apartmentFloorToRelease][apartmentC].numberOfAdults!=0){
                        BlockID[*blockIDNumber].apartment[apartmentFloorToRelease][apartmentC].numberOfAdults=0;
                        BlockID[*blockIDNumber].apartment[apartmentFloorToRelease][apartmentC].numberOfChildren=0;
                        strcpy(BlockID[*blockIDNumber].apartment[apartmentFloorToRelease][apartmentC].apartmentHolders,"none");
                        strcpy(BlockID[*blockIDNumber].apartment[apartmentFloorToRelease][apartmentC].dateOfAccommodation,"none");

                        printf("Congrats! You released %d apartment!\n", apartmentNumberToRelease);
                        (*flag)--;
                        reWritingTheBinaryFile(fp,blockIDNumber);
                    }else{
                        printf("This apartment is already free!\n");
                    }
                }
            }while(apartmentNumberToRelease>(BlockID[*blockIDNumber].floors*BlockID[*blockIDNumber].apartmentsPerFloor) || apartmentNumberToRelease<1);
    }else{
        printf("There is no apartment to release!\n");
    }
}

void menu(FILE *fp,int *flag, int *blockIDNumber, int *numbersOfBlocks){
    int n;

    printf("\nChoose one of the following options!\n");
    printf("1.Accommodation of people.\n");
    printf("2.Release apartment.\n");
    printf("3.Check which floor the elevator is on.\n");
    printf("4.Check entrance fee.\n");
    printf("5.Change block.\n");
    printf("6.Add one more block.\n");
    printf("7.Exit.\n");
    printf("Answer: ");

    scanf("%d",&n);

    switch(n){
        case 1: accommodationOfPeopleNew(flag,fp,blockIDNumber);break;
        case 2: releaseOfTheApartment(flag,fp,blockIDNumber); break;
        case 3: elevator(flag,blockIDNumber);break;
        case 4: entraceFeeChecking(blockIDNumber);break;
        case 5: anotherBlock(blockIDNumber, numbersOfBlocks, fp);break;
        case 6: addOneMoreBlock(numbersOfBlocks);break;
        case 7: closeTheProgram(fp,numbersOfBlocks);break;
    }
}

void allocatingMemory(int numberOfBlocks){

    BlockID = (struct blockInfo *) malloc(numberOfBlocks * sizeof(struct blockInfo));
    if(BlockID == NULL){
        printf("Out of memory for blocks!\n");
        exit(1);
    }
}

void anotherBlock(int *blockIDNumber, int numberOfBlocks, FILE *fp){

    do{
        printf("Which block do you want to work with: ");
        scanf("%d", blockIDNumber);

        if(*blockIDNumber<0 || *blockIDNumber > numberOfBlocks){
            printf("There is no such block! Try Again!\n");
        }

    }while(*blockIDNumber<0 || *blockIDNumber>numberOfBlocks);

    printf("\nBlock: %d\n", *blockIDNumber);
    (*blockIDNumber)--;

    if(checkingFileExistence(fp,*blockIDNumber)==0){
        FloorsAndApartments(*blockIDNumber);
        allocatingMemoryOfOneBlock(*blockIDNumber);
        freeAllApartments(*blockIDNumber);
    }else{
        readingTheFileAndFillTheArray(fp,*blockIDNumber);
    }

}

void elevator(int *flag, int *blockIDNumber){
    int counter=0;
    int maxCounter=0;
    int rememberFloor;

    if(*flag>0){
        for(int i=0;i<BlockID->floors;i++){
            for(int j=0;j<BlockID->apartmentsPerFloor;j++){
                if(i==0){
                    counter+=(BlockID[*blockIDNumber].apartment[i][j].numberOfAdults+BlockID[*blockIDNumber].apartment[i][j].numberOfChildren);
                    counter+=(BlockID[*blockIDNumber].apartment[i+1][j].numberOfAdults+BlockID[*blockIDNumber].apartment[i+1][j+1].numberOfChildren);
                }else if(i==BlockID[*blockIDNumber].floors){
                    counter+=(BlockID[*blockIDNumber].apartment[i][j].numberOfAdults+BlockID[*blockIDNumber].apartment[i][j].numberOfChildren);
                    counter+=(BlockID[*blockIDNumber].apartment[i-1][j].numberOfAdults+BlockID[*blockIDNumber].apartment[i-1][j-1].numberOfChildren);
                }else{
                    counter+=(BlockID[*blockIDNumber].apartment[i][j].numberOfAdults+BlockID[*blockIDNumber].apartment[i][j].numberOfChildren);
                    counter+=(BlockID[*blockIDNumber].apartment[i-1][j].numberOfAdults+BlockID[*blockIDNumber].apartment[i-1][j-1].numberOfChildren);
                    counter+=(BlockID[*blockIDNumber].apartment[i+1][j].numberOfAdults+BlockID[*blockIDNumber].apartment[i+1][j+1].numberOfChildren);
                }
            }
            if(counter>maxCounter){
                maxCounter=counter;
                rememberFloor=i;
            }
            counter=0;
        }
        printf("The elevator goes to the %d floor when not in use!\n",rememberFloor+1);
    }else{
        printf("The elevator goes to the 1 floor when not in use!\n");
    }
}

int main(){
    int blockIDNumber;
    int blockNumber;
    int numberOfBlocks=5;
    int flag=0;
    FILE *fp;

    printf("Welcome!\n");
    printf("By default there are 5 blocks to work with! You can add more if you want!\n");

    allocatingMemory(numberOfBlocks);

    do{
        printf("Which block do you want to work with: ");
        scanf("%d", &blockNumber);

        if(blockNumber<0 || blockNumber>numberOfBlocks){
            printf("There is no such block! Try Again!\n");
        }else{
            printf("Block: %d\n",blockNumber);
            blockIDNumber = blockNumber-1;

            if(checkingFileExistence(fp,blockIDNumber)==0){
                FloorsAndApartments(blockIDNumber);
                allocatingMemoryOfOneBlock(blockIDNumber);
                freeAllApartments(blockIDNumber);
                printf("\n");
            }else{
                readingTheFileAndFillTheArray(fp,blockIDNumber);
            }
       }
    }while(blockNumber<0 || blockNumber>numberOfBlocks);

    do{
        menu(fp,&flag, &blockIDNumber,&numberOfBlocks);
    }while(1);

    return 0;
}
