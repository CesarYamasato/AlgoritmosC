"""BlackJack"""
from pickle import FALSE
import random,sys, time
from playsound import playsound
print(sys.path)

hearts = chr(9829)
diamonds = chr(9830)
spades = chr(9824)
clubs = chr(9827)
backside = 'backside'

suits = {hearts, diamonds, spades,clubs}

def getbet(maxbet):
    bet = input(' >').upper().strip()
    while True:
        if bet.isdecimal():
            if (int(bet) <= maxbet) and (int(bet) >= 1):
                return int(bet)
        elif bet == 'QUIT':
            print('Thanks for playing')
            sys.exit()
        print ("that is not a valid option")
        bet = input(' >').upper().strip()

def getmove(playerHand, money):
    while True:
        moves = ['(H)it', '(S)tand']

        if len(playerHand) == 2 and money > 0:
            moves.append('(D)ouble down')
        movePrompt = ', '.join(moves)
        move = input(movePrompt).upper()
        if move in ('H','S'):
            return move
        if move == "D" and '(D)ouble down' in moves:
            return move

def getHandValue(hand):
    hand = list(hand)
    value = 0
    nmbOfAces = 0
    for cards in hand:
        if cards[0] == 'A':
            nmbOfAces = nmbOfAces + 1
        elif cards[0] in ('J','K', 'Q'):
            value += 10
        else:
            value += int(cards[0])
    value += nmbOfAces
    for i in range(nmbOfAces):
        if value + 10 <= 21:
            value += 10
        else: break
    return value

        
def getDeck():
    deck = []
    for suit in suits:
        for rank in range (2,11):
            deck.append((str(rank),suit))
        for rank in ('J','Q', 'K', 'A'):
            deck.append((str(rank),suit))
    random.shuffle(deck)
    return deck

def DisplayHands(playerHand,dealerHand, showDealerHand):
    if showDealerHand:
        print('DEALER:', getHandValue(dealerHand))
    else:
        print('DEALER: ???')
        DisplayCards([backside] + dealerHand[1:])
    print('PLAYER: ', getHandValue(playerHand))
    DisplayCards(playerHand)

def DisplayCards(hand):
    rows = ['','','','']
    for i, cards in enumerate(hand):
         rows[0] +=   ' ___ ' #top line of the card
         if cards == backside:
             rows [1] += '|## |'
             rows [2] += '|###|'
             rows [3] += '|_##|'
         else:
            rank,suit = cards
            rows [1] += '|{} |'.format(rank.ljust(2))
            rows [2] += '| {} |'.format(suit)
            rows [3] += '|_{}|'.format(rank.rjust(2,'_'))
    for row in rows:
        print(row)

def printinst(money, bet = False):
    if bet:
        print("Do you want to bet or QUIT? (1-",money,", or QUIT)")
    else:
        print ("Select a move")

def main(counter):
    if time.time() - counter >= 180:
        playsound('GameCorner.wav', False)
        counter = time.time()
    money = 5000
    while True:
        #print('counter: \n time.time:', counter, time.time())
        if time.time() - counter >= 180:
            playsound('GameCorner.wav', False)
            counter = time.time()
        
        if money <= 0:
            print("Game Over")
            sys.exit()
        print("Money: ", money)
        printinst(money,True) 
        bet = getbet(money)

        deck = getDeck()
        dealerHand = [deck.pop(),deck.pop()]
        playerHand = [deck.pop(),deck.pop()]
        print('Bet', bet)
        while True:
            DisplayHands(playerHand, dealerHand, False)
            print()
            if getHandValue(playerHand) > 21:
                break
            
            printinst(money)
            move = getmove(playerHand, money - bet)

            if move == 'D':
                additionalBet = getbet(min(bet, (money-bet)))
                bet += additionalBet
                print("Bet increased to {}.".format(bet))
                print("Bet:", bet)
            if move in ('D', 'H'):
                newCard = deck.pop()
                rank, suit = newCard
                print ('You drew a {} of {}'.format(rank, suit))
                playerHand.append(newCard)
                if getHandValue(playerHand) > 21:
                    continue
            if move in ('S', 'D'):
                break
        if getHandValue(playerHand) <= 21:
            while getHandValue(dealerHand) < 17:
                print("Dealer hits...")
                dealerHand.append(deck.pop())
                DisplayHands(playerHand,dealerHand, False)
                if getHandValue(dealerHand) > 21:
                    break
                input('Press enter to continue...')
                print('\n\n')

        DisplayHands(playerHand,dealerHand,True)

        playervalue = getHandValue(playerHand)
        dealervalue = getHandValue(dealerHand)

        if dealervalue > 21:
            print('You won! You get $', bet)
            money += bet
        elif (dealervalue > playervalue) or (playervalue > 21):
            print('You lost! You lose $', bet)
            money -= bet
        elif playervalue > dealervalue:
            print('You won! You get $', bet)
            money += bet
        elif playervalue == dealervalue:
            print('It is a tie, the bet is returned to you')
        
        input("Press enter to continue...")
        print('\n\n')
playsound('GameCorner.wav',False)
if __name__ == '__main__':
    main(time.time())

    