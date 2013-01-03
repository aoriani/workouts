#include <stdio.h>
#include <assert.h>

unsigned add (unsigned a, unsigned b){
    unsigned carry = 0;
    unsigned result = 0x0;
    unsigned bit_insert_pos = 1;
    
    while( a || b) {
        //extract the Lower significant bits
        unsigned a_lsb = a & 0x1;
        unsigned b_lsb = b & 0x1;
        //sum latest bits
        unsigned result_lsb = a_lsb ^ b_lsb ^ carry;
        carry =  (a_lsb & b_lsb)|(a_lsb & carry)|(b_lsb & carry); 
        //insert result_lsb in the proper bit position
        if(result_lsb){
            result |= bit_insert_pos;
        }
        //move to next bit
        bit_insert_pos <<= 1;
        a >>=1; b >>=1;
    }
    
    if(carry){
        result |= bit_insert_pos;
    }
    
    return result;
}   

// O(max(|a|,|b|)) -> |c| == number of bits of c
// O(|c|) == O(lg(c))
unsigned faster_add (unsigned a, unsigned b){
    //Summing bits is similar to xor operation
    unsigned sum = a ^ b;
    //But sum can produce carry if both bits are 1
    unsigned carry = a & b;
    
    //Sum the carry to crrent result. If still produce carry, sum again
    while(carry){
        int shifted_carry = carry<<1; //carry of bit i shall be applied to bit (i+1)
        carry = sum & shifted_carry;
        sum ^= shifted_carry;
    }
    
    return sum;
}

unsigned twoscomplement(unsigned a){
    //flip bits, add 1
    return faster_add(~a,1);
}

//xor trick to swap without extra mem
unsigned swap (unsigned *a, unsigned *b){
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

unsigned subtract(unsigned a, unsigned b){
    //a-b == a + (-b)
    if(a<b) swap(&a,&b);
    return faster_add(a,twoscomplement(b));
}

unsigned multiply(unsigned a, unsigned b){
    //Use definition : add a for b times => O(b*(O(add))
    // use a*b==b*a to loop less times O(min(a,b)*O(add))
    //use x<<y == z * 2^y in a smart way 
    // imitate how multiplication is done by hand 
    /**
     *     11
     *    x10
     *    ----
     *     00
     *    11+
     *   -----
     *    110   => O(|b|*O(add))
     *
     * the last method has smaller complexity O(lg^2(n))
     */
     unsigned sum = 0;
     while(b){
        if(b & 1){
            //only sum if the current bit of multiplier is one
            sum = faster_add(sum,a);            
        }
        //move to next bit of multiplier
        b >>= 1;
        //shift multplicand to left for the next sum
        a <<= 1;
     }
     
     return sum;
}

struct div_t{
    unsigned div;
    unsigned rem;
};


unsigned leftalign(unsigned a, unsigned b){
    assert(a >= b);
    
    unsigned b_aligned = b;
    while(a || b){
        if(!b){
            b_aligned <<=1;
        }else{
            b >>= 1;
        } 
        a >>= 1;
    }
    return b_aligned;
}

struct div_t div(unsigned a, unsigned b){
    assert(b); //Thou shalt not divide by zero !
    
    struct div_t result;
    
    if(b > a){
        result.div = 0;
        result.rem = a;
    }else{
        // division done by hand O(lg(a)-lg(c))
        unsigned ba = leftalign(a,b);
        result.div = 0;
        
        while( ba >= b) {
            result.div <<=1;
            if(a >= ba){
                result.div |= 1;
                a = subtract(a,ba);
            }
            ba >>=1;
        }           
        result.rem = a;
    }

    return result;
}

int main(){
    
    struct div_t result = div(35,35);
    
    printf("Result is (%u,%u) \n",result.div,result.rem);

    return 0;
}
