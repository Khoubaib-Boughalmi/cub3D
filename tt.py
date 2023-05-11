import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

last=4
# game loop
list=[]
while True:
    action_count = int(input())  # the number of spells and recipes in play
    for i in range(action_count):
        inputs = input().split()
        list.append(inputs)
        action_id = int(inputs[0])  # the unique ID of this spell or recipe
        action_type = inputs[1]  # in the first league: BREW; later: CAST, OPPONENT_CAST, LEARN, BREW
        delta_0 = int(inputs[2])  # tier-0 ingredient change
        delta_1 = int(inputs[3])  # tier-1 ingredient change
        delta_2 = int(inputs[4])  # tier-2 ingredient change
        delta_3 = int(inputs[5])  # tier-3 ingredient change
        price = int(inputs[6])  # the price in rupees if this is a potion
        tome_index = int(inputs[7])  # in the first two leagues: always 0; later: the index in the tome if this is a tome spell, equal to the read-ahead tax; For brews, this is the value of the current urgency bonus
        tax_count = int(inputs[8])  # in the first two leagues: always 0; later: the amount of taxed tier-0 ingredients you gain from learning this spell; For brews, this is how many times you can still gain an urgency bonus
        castable = inputs[9] != "0"  # in the first league: always 0; later: 1 if this is a castable player spell
        repeatable = inputs[10] != "0"  # for the first two leagues: always 0; later: 1 if this is a repeatable player spell
    for i in range(2):
        # inv_0: tier-0 ingredients in inventory
        # score: amount of rupees
        inv_0, inv_1, inv_2, inv_3, score = [int(j) for j in input().split()]
        my_0=inv_0
        my_1=inv_1
        my_2=inv_2
        my_3=inv_3
        print(my_0," ",my_1," ",my_2," ",my_3," ",score, file=sys.stderr, flush=True)
    # print(tome_index," ",tax_count," ",castable," ",repeatable, file=sys.stderr, flush=True)
    price=0
    brew_list = [elem for elem in list if elem[1] == 'BREW']
    cast_list = [elem for elem in list if elem[1] == 'CAST']

    print(list," ", file=sys.stderr, flush=True)
    # print(my_0, my_1, my_2, my_3, file=sys.stderr, flush=True)
    save=-1
    i=0
    for el in brew_list:
        # print(score,"  ",int(el[2]),my_0,"  ",int(el[3]),my_1,"  ",int(el[4]),my_2,"  ",int(el[5]),my_3,"  "," ", file=sys.stderr, flush=True)
        yes=1
        if(int(el[2])+my_0<0):
            yes=0
        if(int(el[3])+my_1<0):
            yes=0
        if(int(el[4])+my_2<0):
            yes=0
        if(int(el[5])+my_3<0):
            yes=0
        if int(el[6])>price and yes==1:
            price=int(el[6])
            save=i
        i+=1
    if(save==-1):
        did=0
        for el in cast_list:
            # print(el[9]," ", file=sys.stderr, flush=True)
            if(el[9]=='1' and not did):
                print(int(el[2]),my_0,"  ",int(el[3]),my_1,"  ",int(el[4]),my_2,"  ",int(el[5]),my_3,"  "," ", file=sys.stderr, flush=True)
                num = my_0+my_1+my_2+my_3 + int(el[2]) + int(el[3]) + int(el[4]) + int(el[5])
                yes=1
                if(int(el[2])+my_0<0 and int(el[2])+my_0>3):
                    yes=0
                if(int(el[3])+my_1<0 and int(el[3])+my_1>3):
                    yes=0
                if(int(el[4])+my_2<0 and int(el[4])+my_2>3):
                    yes=0
                if(int(el[5])+my_3<0 and int(el[5])+my_3>3):
                    yes=0
                print(yes," ", file=sys.stderr, flush=True)
                if(num<10):
                    print("CAST",el[0])
                    did=1
        if(did==0):
            print("REST")
        #     last=5
        # else:
        #     print("CAST",list[last][0])
        #     last+=1
    else:
        print("BREW ",brew_list[save][0])
    print("so ",save, file=sys.stderr, flush=True)

    # Write an action using print


    # in the first league: BREW <id> | WAIT; later: BREW <id> | CAST <id> [<times>] | LEARN <id> | REST | WAIT
    list.clear()
















