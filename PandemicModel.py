#nick latham
#very simple model to serve as a basis

import math
import numpy as np  
import matplotlib.pyplot as plt  


def main():
    infection_rate = int(input("What is the infection rate -->"))
    hospital_rate = float(input("what is the rate at which the sick need hospital care? e.g. if 20.5%, enter 20.5 -->"))
    death_rate = float(input("what is the death rate? -->"))
    population = int(input("what is the population? -->"))
    sick = int(input("How many are sick? The amount entered needs to be between 1 and the population -->"))
    while(sick < 1 or sick > population):
        sick = int(input("enter a correct value -->"))
    hospital_capicity = int(input("What is the hospital capicity? -->"))
    iterations = int(input("how many days do you want to model? -->"))
    overflow = 0
    recovered = 0
    dead = 0
    havent_got_it_yet = population - sick
    in_hospital = 0
    sick_exp = sick
    total_sick = sick

    count = 0
    done = False
    x = []
    y = []
    while count < iterations and not done:
        x.append(count)
        y.append(sick)
        print("day ", count, ": sick: ", sick, "haven't got it: ", havent_got_it_yet, " recovered: ", recovered, "dead: ", dead)
        sick = int(sick*infection_rate) #each of the sick people will pass it on
        # sick = int(sick_exp*infection_rate) #alternate way to represent exponenential growth
        # sick_exp *= infection_rate
        sick = math.ceil(sick*(havent_got_it_yet/(sick+recovered+havent_got_it_yet))) #but only the share of the population that hasnt got it yet
        if sick > havent_got_it_yet:
            sick = havent_got_it_yet
        havent_got_it_yet -= sick
        in_hospital = math.ceil(hospital_rate*.01*sick) #some of the sick people will have to go to the hospital
        if in_hospital > hospital_capicity: #there might not be enough capacity
            overflow = in_hospital-hospital_capicity #those without hospital care
            in_hospital = hospital_capicity #update the number in the hospital
        else:
            overflow = 0
        dead += int(death_rate*.01*sick) #some of the sick will die
        dead += overflow            #all the overflow will die
        recovered += sick-overflow-int(death_rate*.01*sick) #add up the recovered
        total_sick += sick
        if sick < 1:
            done = True
        count += 1

    print("dead: ", dead)
    print("recovered: ", recovered)
    plt.plot(x,y)
    x = [0,iterations]
    y = [hospital_capicity, hospital_capicity]
    plt.plot(x,y)

main()
plt.show()
