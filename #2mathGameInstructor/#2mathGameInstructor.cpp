// #2mathGameInstructor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std; 

enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };
enum enQuestionsLevel{ EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };

struct stQuestion{ 
    int Number1 = 0;
    int Number2 = 0; 
    enOperationType OperationType;
    enQuestionsLevel QuestionLevel;
    int CorrectAnswer = 0; 
    int PlayerAnswer = 0;
    bool AnswerResult = false;

};
struct stQuizz
{
    stQuestion QuestionList[100];
    short NumberOfQuestions;
    enQuestionsLevel QuestionsLevel;
    enOperationType OpType; 
    short NumberOfWrongAnswers = 0;
    short NumberOfRightAnswers = 0;
    bool isPass = false;
};

int RadnomNumber(int from, int to) {
    int RandomNumm = rand() % (to - from + 1) + from;
    return RandomNumm;
}
short ReadHowManyQuestion() {

    short NumberOfQuestions; 
    do { 
        cout << "How Many Questions do you want to answer ? "; 
        cin >> NumberOfQuestions; 
    } while (NumberOfQuestions < 1 || NumberOfQuestions > 10);
    return NumberOfQuestions;
}

enQuestionsLevel ReadQuestionsLevel() {
    short QuestionLevel = 0; 
    do { 
        cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";   
        cin >> QuestionLevel;
    } while (QuestionLevel < 1 || QuestionLevel >4); 
    return (enQuestionsLevel)QuestionLevel;
};
enOperationType  ReadOpType() {
    short OpType;
    do { 
        cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";    
        cin >> OpType; 
    } while (OpType < 1 || OpType >5);
        return (enOperationType)OpType;
};
enOperationType GetRandomOperationType() {
    int op = RadnomNumber(1, 4);

    return (enOperationType)op;
}

int ReadQuestionAnswer() {
    int Answer = 0;
    cin >> Answer;
    return Answer;
}

void SetScreenColor(bool Right) {
    if (Right) {
        system("color 2F");
    }
    else {
        system("color 4F");
        cout << "\a";
    }
}

string GetOpTypeSymbol(enOperationType OpType) {
    switch (OpType)
    {
    case enOperationType::Add:
        return "+";
    case enOperationType::Sub:
        return "-";
    case enOperationType::Mult:
        return "*";
    case enOperationType::Div:
        return "/" ;

    default:
        return "Mix";
    }
}

string GetQuestionLevelText(enQuestionsLevel QuestionLevel) {
    string arrQuestionLevelText[4] = { "Easy", " Med" , "Hard" , "Mix" };
    return arrQuestionLevelText[QuestionLevel - 1];

}

int SimpleCalculator(int number1 ,int number2 , enOperationType OpType){

    switch (OpType)
    {
    case enOperationType::Add:
        return number1 + number2; 
    case enOperationType::Sub:
        return number1 - number2;
    case  enOperationType::Mult:
        return number1 * number2;
    case  enOperationType::Div:
        return number1 / number2;
    
    default:
        return number1 + number2;
    }
}


stQuestion GenerateQuestion (enQuestionsLevel QuestionLevel , enOperationType OpType){

    stQuestion Question;
    if (QuestionLevel == enQuestionsLevel::Mix){
        
        QuestionLevel = (enQuestionsLevel)RadnomNumber(1, 3);

    }
    if (OpType  == enOperationType::MixOp) {
        OpType = GetRandomOperationType();
        
    }

    Question.OperationType = OpType;
    switch (QuestionLevel)
    {
    case enQuestionsLevel::EasyLevel:
        Question.Number1 = RadnomNumber(1, 10);
        Question.Number2 = RadnomNumber(1, 10);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;

    case enQuestionsLevel::MedLevel:
        Question.Number1 = RadnomNumber(1, 50);
        Question.Number2 = RadnomNumber(1, 50);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;
    case enQuestionsLevel::HardLevel:
        Question.Number1 = RadnomNumber(1, 100);
        Question.Number2 = RadnomNumber(1, 100);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;
    }
    return Question;


}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber) {
    if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer) {

        Quizz.QuestionList[QuestionNumber].AnswerResult = false;
        Quizz.NumberOfWrongAnswers++;

        cout << "Wrong Answer :-( \n";
        cout << " The right answer";
        Quizz.QuestionList[QuestionNumber].CorrectAnswer;
        cout << "\n"; 

    }

    else {

        Quizz.QuestionList[QuestionNumber].AnswerResult = true;
        Quizz.NumberOfRightAnswers++; 
        cout << "right answer :-) \n";

    }
    cout << endl;

    SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);

}

void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber) {
    cout << "\n";
    cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "] \n\n "; 
    cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
    cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
    cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
    cout << "\n_________________\n";
}

void AskAndCorrectQuestionListAnwers(stQuizz& Quizz) {
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++) {

        PrintTheQuestion(Quizz, QuestionNumber);
        Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
        CorrectTheQuestionAnswer(Quizz, QuestionNumber);
    }
    Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

void GenerateQuizzQuestion(stQuizz& Quizz) {

    for (short question = 0; question < Quizz.NumberOfQuestions; question++) {
        Quizz.QuestionList[question] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OpType);
    }
}
string GetFinalResultsText(bool pass) {
    if (pass) {
        return "Pass";
    }
    else {
        return "Failed";
    }
}
void PrintQuizzResult(stQuizz Quizz) {
    cout << "\n";
    cout << "--------------------------\n\n";

    cout << "FInal Result is " << GetFinalResultsText(Quizz.isPass);
    cout << "\n--------------------------\n\n";
    cout << " Number of Questions: " << Quizz.NumberOfQuestions << endl; 
    cout << " Questions Level   : " << GetQuestionLevelText(Quizz.QuestionsLevel) << endl;
    cout << " OpType   : " << GetOpTypeSymbol(Quizz.OpType) << endl;
    cout << " number of Right answer   : " << Quizz.NumberOfRightAnswers << endl;
    cout << " number of Wrong Answer   : " << Quizz.NumberOfWrongAnswers << endl;
    cout << "-------------------------------------------\n";
}

void PlayMathGame() {
    stQuizz Quizz;
    Quizz.NumberOfQuestions = ReadHowManyQuestion();
    Quizz.QuestionsLevel = ReadQuestionsLevel();   
    Quizz.OpType = ReadOpType();

    GenerateQuizzQuestion(Quizz); 
    AskAndCorrectQuestionListAnwers(Quizz);
    PrintQuizzResult(Quizz); 



}

void ResetScreen() { 
    system("cls");     
    system("color 0F"); 

} 

void StartGame() { 
    char PlayAgain = 'Y';
    do { ResetScreen();       
    PlayMathGame();   
    cout << endl << "Do you want to play again? Y/N? ";     
    cin >> PlayAgain; } while (PlayAgain == 'Y' || PlayAgain == 'y'); 


}
int main()
{
    srand((unsigned) time(NULL));
    StartGame();
    
}
