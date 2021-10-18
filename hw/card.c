#include <stdio.h>
#include <stdlib.h>

int N,M,K;//N players, M cards, K people with joker
int *joker_person={0};

typedef struct card{
    int number;//joker = -1
    struct card *next; 
} Card;

typedef struct player{
    int index;
    Card *first_card;
    int joker; //if there is joker, change to 1
    struct player *next;
} Player;

Player *NewPlayer(int joker, int total_cards){
    Player *newplayer = (Player *)malloc(sizeof(Player));
    newplayer->next = newplayer;//circular linkedlist for player
    newplayer->first_card = (Card *)malloc(sizeof(Card));
    newplayer->first_card->number = 0;//set the first card as a empty space
    newplayer->first_card->next = NULL;//singular linkedlist for cards
    Card *add_card = (Card *)malloc(sizeof(Card));//newcard to add after the empty space
    Card *newcard = newplayer->first_card;
    if (joker){
        newplayer->joker = 1;//record  the player has a joker in hand
        add_card->number = -1;//the first card
    }
    else{
        newplayer->joker = 0;//record  the player has no joker in hand
        add_card->number = 1;
    }
    //connect to the first empty card
    newcard->next = add_card;
    add_card->next = NULL;
    newcard = add_card;
    //complete the rest of the card set
    for(int i = 2; i <= total_cards; ++i){
        add_card = (Card *)malloc(sizeof(Card));
        add_card->number = i;
        newcard->next = add_card;
        add_card->next = NULL;
        newcard = add_card;
    }
    return newplayer;
}


Player *init_player(int total_players){
    int i = 1;//the player start from 1 since it is a linkedlist
    int j = 0;//the index of joker_person array
    Player *first_player = NULL;
    Player *nowplayer = NULL;
    Player *addplayer = NULL;
    
    while(i <= total_players){
        if(i == joker_person[j]){
            addplayer = NewPlayer(1, M);
            j++;
        }
        else addplayer = NewPlayer(0, M);
        if(i == 1){//set the head of the player
            addplayer->index = i;
            first_player = addplayer;
            nowplayer = first_player;
        }
        else{
            if(nowplayer == NULL){
                return NULL;
            }
            else{
                addplayer->index = i;
                addplayer->next = nowplayer->next;
                nowplayer->next = addplayer;
                nowplayer = nowplayer->next;
            }   
        }
        ++i;
    }
    return first_player;
}



Card *find_take_position(int position, Card *first_card){
    Card *nowcard = first_card;//start from the empty space
    //assure the targetcard->next is NULL
    for(int i = 1; i < position && nowcard->next->next != NULL; ++i){
        nowcard = nowcard->next;
    }
    return nowcard;//return the pre_position
}

Card *find_put_position(int position, Card *first_card){
    Card *nowcard = first_card;//start from the empty space
    //only have to check the next node is NULL
    for(int i = 1; i < position && nowcard->next != NULL; ++i){
        nowcard = nowcard->next;
    }
    return nowcard;//return the pre_position
} 

void draw_card(Player *takedcard_player, Player *putcard_player, int take, int put){
    Card *pretake = find_take_position(take, takedcard_player->first_card);
    Card *preput = find_put_position(put, putcard_player->first_card);
    Card *targetcard = pretake->next;
    //to change the joker amount in both player
    if(targetcard->number == -1){
        takedcard_player->joker -= 1;
        putcard_player->joker += 1;
    }
    pretake->next = targetcard->next;
    targetcard->next = preput->next;
    preput->next = targetcard;
    return;
}

void print_result(Player *first_player){
    Player *now_player = first_player;
    while(now_player != NULL){
        if(now_player->joker == 1){
            now_player = now_player->next;
            continue;
        }
        else{
            Card *nowcard = now_player->first_card->next;//start from the first card with number
            if(nowcard == NULL){
                printf("\n");
                break;
            }
            while(nowcard != NULL){
                printf("%d%c", nowcard->number, '\n'*(nowcard->next == NULL)+' '*(nowcard->next != NULL));
                nowcard = nowcard->next;
            }
            break;
        }
    }
    return;
}

int main (){
    int take = 0;//i
    int put = 0;//j
    scanf("%d", &N);
    scanf("%d", &M);
    scanf("%d", &K);
    joker_person = (int *) malloc(K * sizeof(int));
    for(int i = 0;i < K;++i){
        scanf("%d", &joker_person[i]);
    }
    Player *first_player = init_player(N);
    Player *cardput_player = first_player;
    Player *cardtaked_player = cardput_player->next;

    while(scanf("%d %d", &take, &put)!= EOF){
        if(take == -1 && put == -1)break;
        draw_card(cardtaked_player, cardput_player, take, put);
        cardput_player = cardput_player->next;
        cardtaked_player = cardput_player->next;
    }
    print_result(first_player);
    return 0;
}