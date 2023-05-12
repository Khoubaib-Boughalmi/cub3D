import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.
reset =4
last=4
brewed =0
# game loop
list=[]
list_want=[0,0,0,0]
my_inve=[0,0,0,0]

# def test_double(list,learn_list,brew_list,cast_list,my_inve):
#     print(list," ", file=sys.stderr, flush=True)
#     print(learn_list," ", file=sys.stderr, flush=True)

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
        if(i==0):
            my_0=inv_0
            my_1=inv_1
            my_2=inv_2
            my_3=inv_3
            my_inve[0]=inv_0
            my_inve[1]=inv_1
            my_inve[2]=inv_2
            my_inve[3]=inv_3
            print(my_0," ",my_1," ",my_2," ",my_3," ",score, file=sys.stderr, flush=True)
    # print(tome_index," ",tax_count," ",castable," ",repeatable, file=sys.stderr, flush=True)
    price=0
    OPPONENT_CAST = [elem for elem in list if elem[1] == 'OPPONENT_CAST']
    learn_list = [elem for elem in list if elem[1] == 'LEARN']
    brew_list = [elem for elem in list if elem[1] == 'BREW']
    cast_list = [elem for elem in list if elem[1] == 'CAST']
    for el in brew_list:
        list_want[0]+=int(el[2])*-1
        list_want[1]+=int(el[3])*-1
        list_want[2]+=int(el[4])*-1
        list_want[3]+=int(el[5])*-1
    if list_want[0] >6:
        list_want[0]=6
    if list_want[1] >6:
        list_want[1]=6
    if list_want[2] >6:
        list_want[2]=6
    if list_want[3] >6:
        list_want[3]=6
    if list_want[0] <2:
        list_want[0]=2
    if list_want[1] <2:
        list_want[1]=2
    if list_want[2] <2:
        list_want[2]=2
    if list_want[3] <2:
        list_want[3]=2
    print(list," ", file=sys.stderr, flush=True)
    # print(brew_list," ", file=sys.stderr, flush=True)
    # print(list_want,"wanted  ", file=sys.stderr, flush=True)
    # print(my_0, my_1, my_2, my_3, file=sys.stderr, flush=True)
    brewed = brewed %10
    learned =0
    print(len(brew_list)," ", file=sys.stderr, flush=True)
    for el in learn_list:
        if brewed > 3 or len(cast_list)>7:
            break
        learned =1
        print("LEARN",el[0])
        brewed+=1
        # print(el," ", file=sys.stderr, flush=True)
        break


    if not learned :
        save=-1
        # i=0
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
            # i+=1
        if(save==-1):
            did=0
            choosen=-1
            large=-1
            big_large=-1
            # i=0
            for el in cast_list:
                # print(el[9]," ", file=sys.stderr, flush=True)
                if(el[9]=='1' ):
                    num = my_0+my_1+my_2+my_3 + int(el[2]) + int(el[3]) + int(el[4]) + int(el[5])
                    yes=1
                    if(int(el[2])+my_0<0 or int(el[2])+my_0>list_want[0]):
                        yes=0
                    if(int(el[3])+my_1<0 or int(el[3])+my_1>list_want[1]):
                        yes=0
                    if(int(el[4])+my_2<0 or int(el[4])+my_2>list_want[2]):
                        yes=0
                    if(int(el[5])+my_3<0 or int(el[5])+my_3>list_want[3]):
                        yes=0
                    # print(yes," ", file=sys.stderr, flush=True)
                    if(num<10 and yes):
                        print("casted",el[0],int(el[2]),my_0,"  ",int(el[3]),my_1,"  ",int(el[4]),my_2,"  ",int(el[5]),my_3,"  "," ", file=sys.stderr, flush=True)
                        for_every_cast=0
                        for l in brew_list:
                            cool=0
                            for i in range(2,6):
                                if int(el[i])+my_inve[i-2]+int(l[i])>=0:
                                    cool+=1
                            for_every_cast+=cool
                            if(cool >= large):
                                large =cool
                                choosen=int(el[0])
                            print("cool ",cool, file=sys.stderr, flush=True)
                        print("for every ",for_every_cast, file=sys.stderr, flush=True)
                            # if not did  and cool==4:
                            #         # print("CAST",el[0])
                            #         brewed-=1
                            #         # did=1
                            #         print("catched ",l, file=sys.stderr, flush=True)
                            #         print("then ",el, file=sys.stderr, flush=True)
                        # if not did :
                        #     print("CAST",el[0])
                        #     brewed+=1
                        #     did=1
                            # print("choosed ",i, file=sys.stderr, flush=True)
                        # i+=1
            print("choosed ",choosen, file=sys.stderr, flush=True)
            print("large ",large, file=sys.stderr, flush=True)
            # if large !=4:
            #     test_double(list,learn_list,brew_list,cast_list,my_inve)
            if(choosen!=-1):
                did=1
                print("CAST",choosen)
                brewed+=1
            if(did==0):
                # print("LEARN",OPPONENT_CAST[0][0])
                if reset==2 or reset ==0 or reset ==-2:
                    print("REST")
                else :
                    if(len(learn_list)):
                        print("LEARN",learn_list[0][0])
                    else:
                        print("REST")
                brewed=2
                reset -=1
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
    list_want=[0,0,0,0]

