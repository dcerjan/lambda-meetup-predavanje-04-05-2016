#include <stdio.h>

#include "Types.h"
#include "List.h"


DefineList(Double);
DefineList(Float);
DefineList(Int);


void simpleExample();
void sortExample();
void filterExample();
void mapExample();
void reduceExample();
void pointersExample();
void wtfExample();


int main(int argc, const char** argv) {
    #ifdef SIMPLE
        simpleExample();
    #elif SORT
        sortExample();
    #elif FILTER
        filterExample();
    #elif MAP
        mapExample();
    #elif REDUCE
        reduceExample();
    #elif POINTERS
        pointersExample();
    #elif WTF
        wtfExample();
    #else
        printf("Nothing to see here, move along");
    #endif

    printf("\n\n");
    return 0;
}


#ifdef SIMPLE
    DefineList(List_Int);

    void simpleExample() {
        List(Int) primes = NewList(Int);

        Push(primes, 2);
        Push(primes, 3);
        Push(primes, 5);
        Push(primes, 7);

        Log("showing list of primes");
        Show(List_Int, primes);
        Endl();


        List(List_Int) listOfLists = NewList(List_Int);

        listOfLists = Push(listOfLists, primes);
        listOfLists = Push(listOfLists, primes);
        listOfLists = Push(listOfLists, primes);

        Endl();
        Log("showing list of lists of primes");
        Show(List_List_Int, listOfLists);
        Endl();

        Free(primes);
        Free(listOfLists);
    }
#elif SORT
    void sortExample() {
        List(Float) numbers = NewList(Float);

        Push(numbers, -3.0f);
        Push(numbers, 2.0f);
        Push(numbers, -0.1f);
        Push(numbers, 4.1f);

        Log("showing list of numbers");
        Show(List_Float, numbers); Endl(); Endl();

        Sort(numbers, a, b, { a < b; });
        Log("showing list of numbers sorted high to low");
        Show(List_Float, numbers); Endl(); Endl();

        Sort(numbers, a, b, { a > b; });
        Log("showing list of numbers sorted low to high");
        Show(List_Float, numbers); Endl();

        Free(numbers);
    }
#elif FILTER
    void filterExample() {
        List(Int) numbers = NewList(Int);

        int i;
        for(i = 0; i < 10; ++i) {
            Push(numbers, i);
        }

        Log("showing list of numbers");
        Show(List_Int, numbers); Endl(); Endl();

        List(Int) filtered = Filter(Int, numbers, element, _, {
            element % 2;
        });
        //Show(List_Int, numbers);

        Log("showing filtered list of numbers");
        Show(List_Int, filtered); Endl(); Endl();

        Free(numbers);
        Free(filtered);
    }
#elif MAP
    void mapExample() {
        List(Int) numbers = NewList(Int);
        int i;
        for(i = 0; i < 10; ++i) {
            Push(numbers, i);
        }
        Log("showing list of numbers");
        Show(List_Int, numbers); Endl(); Endl();

        List(Int) doubles = Map(Int, numbers, x, _, {
            x * 2;
        });
        Log("showing mapped list of numbers");
        Show(List_Int, doubles); Endl(); Endl();

        Free(numbers);
        Free(doubles);
    }
#elif REDUCE
    typedef struct _Vector2 {
        Double x, y;
    } Vector2;

    void Show_Vector2(Vector2 vec) {
        fprintf(stdout, "{x: %g, y: %g}", vec.x, vec.y);
    }

    DefineList(Vector2);

    void reduceExample() {
        List(Vector2) polygon = NewList(Vector2);
        Push(polygon, (Vector2){0.0 $ 0.0});
        Push(polygon, (Vector2){1.0 $ 0.0});
        Push(polygon, (Vector2){1.0 $ 1.0});
        Push(polygon, (Vector2){0.0 $ 1.0});

        Log("showing list of vectors in polygon");
        Show(List_Vector2, polygon); Endl(); Endl();


        Vector2 midpoint = Reduce(Vector2, polygon, memo, point, _, {
            memo.x += point.x;
            memo.y += point.y;
            memo;
	    }, {.x = -100 $ .y = 10});

        Double oneOverLength = 1.0 / (Double)polygon->size;
        midpoint.x *= oneOverLength;
        midpoint.y *= oneOverLength;

        Log("showing reduced center of polygon");
        Show(Vector2, midpoint);
        Free(polygon);
    }
#elif POINTERS
    int idCounter;

    struct Contact {
        String  name;
        String  number;
        Int     id;
        Double  balance;
    };

    typedef struct Contact* Contact;

    Contact NewContact(const String name, const String number, Double balance) {
        Contact contact = (Contact)malloc(sizeof(struct Contact));
        contact->name = (String)malloc(sizeof(Char) * (strlen(name) + 1));
        contact->number = (String)malloc(sizeof(Char) * (strlen(number) + 1));
        strcpy(contact->name, name);
        strcpy(contact->number, number);
        contact->id = ++idCounter;
        contact->balance = balance;
        return contact;
    }

    void FreeContact(Contact* contact) {
        free((*contact)->name);
        free((*contact)->number);
        free((*contact));
        *contact = NULL;
    }

    void Show_Contact(Contact contact) {
        fprintf(stdout, "{id: %d, name: \"%s\", number: \"%s\", balance: %.2f}", contact->id, contact->name, contact->number, contact->balance);
    }

    DefineList(Contact);

    void pointersExample() {

        List(Contact) phonebook = NewList(Contact);

        phonebook = Push(phonebook, NewContact("The Investigator", "+Venus ring/1", 0.0));
        phonebook = Push(phonebook, NewContact("Jim Holden", "+Rocinonte jh/1", 4235.0));
        phonebook = Push(phonebook, NewContact("Josephus Aloisus Miller", "+Ceres jam/42", 600.0));

        Log("showing contacts in phonebook\n[");
        Each(phonebook, contact, index, {
            fprintf(stdout, "  ");
            Show(Contact, contact);
            if(index < phonebook->size -1) {
                Log(",");
            } else {
                Log("");
            }
        });
        Log("]\n");

        List(Int) ids = Map(Int, phonebook, contact, _, { contact->id; });
        Log("showing list of contact ids");
        Show(List_Int, ids); Endl(); Endl();


        Double balance = Reduce(Double, phonebook, memo, contact, _, {
            memo += contact->balance;
        }, 0.0);

        Log("showing total balance of contacts");
        Show(Double, balance); Endl(); Endl();

        Each(phonebook, contact, _, { FreeContact(&contact); });
        Free(phonebook);
        Free(ids);
    }
#elif WTF
    void wtfExample() {
        List(Double) numbers = NewList(Double);

        numbers = Push(numbers, 3.14);
        numbers = Push(numbers, 2.71);
        numbers = Push(numbers, 9.81);

        Log("showing list of numbers");
        Show(List_Double, numbers); Endl(); Endl();


        List(Double) doubles = Map(Double, numbers, x, _, { x * x; });
        Log("showing list of doubled numbers");
        Show(List_Double, doubles); Endl(); Endl();

        Double sum = Reduce(Double, doubles, memo, element, _, { memo += element; }, 0.0);

        Log("showing sum of doubled numbers");
        Show(Double, sum); Endl(); Endl();

        List(Double) strange = Map(Double, numbers, _, i, {
            Reduce(Double, Map(Double, doubles, _, j, {i * j;}), memo, element, _, {memo += element;}, i);
        });

        Log("showing map over map-reduced list of multiplied indices of doubles list");
        Show(List_Double, strange); Endl(); Endl();
    }
#endif
