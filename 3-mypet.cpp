#include <iostream>

typedef struct Animal
{
    char name[30];
    int age;
    int health;
    int food;
    int clean;

} Animal;
void create_animal(Animal *animal)
{
    std::cout << "동물의 이름은 ?";
    std::cin >> animal->name;

    std::cout << "동물의 나이 ? ";
    std::cin >> animal->age;

    animal->health = 100;
    animal->food = 100;
    animal->clean = 100;
}
void play(Animal *animal)
{
    animal->health += 10;
    animal->food -= 20;
    animal->clean -= 30;
}
void show_stat(Animal *animal)
{
    std::cout << animal->name << "의 상태" << std::endl;
    std::cout << "체력 : " << animal->health << std::endl;
    std::cout << "배부름 : " << animal->food << std::endl;
    std::cout << "청결    : " << animal->clean << std::endl;
}
void one_day_pass(Animal **list, int animal_num)
{
    for (int i = 0; i < animal_num; i++)
    {
        list[i]->health -= 10;
        list[i]->food -= 30;
        list[i]->clean -= 20;
    }
}
int main()
{
    Animal *list[10];
    int aniaml_num = 0;

    while (1)
    {
        std::cout << "1. 동물 추가하기" << std::endl;
        std::cout << "2. 놀기" << std::endl;
        std::cout << "3. 상태 보기" << std::endl;
        std::cout << "4. 종료" << std::endl;
        int user_choice;
        std::cin >> user_choice;
        switch (user_choice)
        {
        case 1:
            list[aniaml_num] = new Animal;
            create_animal(list[aniaml_num]);
            aniaml_num++;
            break;
        case 2:
            std::cout << "누구랑 놀게 ? : ";
            int play_with;
            std::cin >> play_with;
            if (play_with < aniaml_num)
                play(list[play_with]);
            break;
        case 3:
            std::cout << "누구껄 보게 ? : ";
            int to_see;
            std::cin >> to_see;
            if (to_see < aniaml_num)
                show_stat(list[to_see]);
            break;
        case 4:
            std::cout<<"종료\n";
            for (int i = 0; i < aniaml_num; i++)
                delete list[i];
            return 0;
        }

        one_day_pass(list, aniaml_num);
    }
    
    return 0;
}
