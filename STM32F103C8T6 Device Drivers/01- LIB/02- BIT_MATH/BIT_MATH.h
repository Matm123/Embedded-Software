/*******************************************/
/* Author  : Mahmoud Ayman                 */
/* Date    : 29 OCT 2020                   */
/* Version : V01                           */
/*******************************************/

#ifndef BIT_MATH_H
#define BIT_MATH_H

#define ONE                       1


#define SET_BIT(VAR,BIT)          VAR |=  (ONE << BIT) 
#define CLR_BIT(VAR,BIT)          VAR &= ~(ONE << BIT)
#define GET_BIT(VAR,BIT)          (VAR >> BIT)  &  ONE
#define TOG_BIT(VAR,BIT)          VAR ^=  (ONE << BIT)



#endif /* BIT_MATH_H */