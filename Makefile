#Sebastian Azamar Aviles
#Karime Aylen de la Cruz
#Carolina Gonzalez Gonzalez
#Martin Granados Reyes
# build
compilar:
        mkdir -p ./build
        g++ -g -std=c++11 -o ./dekker dekker.cpp -pthread

#En caso de querer compilar peterson usar:
#compilar:
#        mkdir -p ./build
#        g++ -g -std=c++11 -o ./peterson peterson.cpp -pthread
