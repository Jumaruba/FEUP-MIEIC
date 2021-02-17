//
// Created by maruba on 06/11/19.
//

#ifndef AEDA_PROJ1_UTILS_H
#define AEDA_PROJ1_UTILS_H
#include "Empresa.h"
#include <cstdlib>
/**
 * @file utils.h
 * @brief Some functions that are useful in the project
 */
/**
 * @brief 
 * 
 * @param min Minimnum value for the number
 * @param max Maximum value for the number
 * @return return the input case it's not a string and it's betweeen min and max. Else throw an exception and waits the person to try agani
 */
int checkOption(int min, int max);   
/**
 * @brief It checks if the id given already exists and if it's not a string. Case wrong input, asks the person to try again. 
 * 
 * @param e enterprise
 * @return Case valid input, return it's value
 */
int validServiceId(Empresa &e);         
/**
 * @brief It checks if the nif given is not a string and if there's a client with this nif
 * 
 * @param e 
 * @return return the nif there's some client with this id and if it's not a string
 */
int validClientNif(Empresa &e);
/**
 * @brief Checks if the input given is a number, not a string
 * 
 * @return return the number case it's a number
 */
double checkNumber();
/**
 * @brief Function makes the user waits until it presses enter
 * 
 */
void wait();
/**
 * @brief Clear screen for both windows and linux 
 * 
 */
void clear_screen();

#endif //AEDA_PROJ1_UTILS_H
