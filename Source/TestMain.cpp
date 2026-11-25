#include <stdio.h>

void SayYourCall() {
    static int call_number = 0;
    printf("You called me %d\n", call_number++);
}

int main(){

    SayYourCall();
    SayYourCall();
    SayYourCall();

}
