#include <iostream>

enum StudentsTraits {
    stAttendsClasses = 1,
    stDoesHWs = 2,
    stLikesSubject = 4,
    stAsksQuestions = 8
}; 



bool checkAttendsClasses(int studentTraits)
{
    return true;
}

int main()
{
    int st = stAttendsClasses;
    st |= stDoesHWs;
    checkAttendsClasses(st);
    return 0;
}
