#include "../cJSON.h"
#include <stdio.h>
#include <string.h>

typedef struct{
    char firstName[32];
    char lastName[32];
    char email[64];
    int age;
    float height;
}PERSON;

void cJSONTest1(void)
{
    //解析一个键值对
    char *data = "{\"firstName\":\"Brett\"}";

    //从缓冲区中解析json结构
    cJSON *root = cJSON_Parse(data);
    if(!root)return;

    cJSON *item = cJSON_GetObjectItem(root,"firstName");
    if(!item)return;

    printf("%s : %s\n",item->string,item->valuestring);

    cJSON_Delete(root);
}

void cJSONTest2(void)
{
    //解析一个结构体
    typedef struct{
        char firstName[32];
        char lastName[32];
        char email[64];
        int age;
        float height;
    }PERSON;

    char *data = "{\"person\":{\"firstName\":\"z\",\"lastName\":\"jadena\",\"email\":\"jadena@126.com\",\"age\":8,\"height\":1.17}}";

    cJSON *root = cJSON_Parse(data);
    if(!root)return;

    cJSON *obiect = cJSON_GetObjectItem(root,"person");
    if(!obiect)return;

    cJSON *item;
    PERSON person;

    memset(person.firstName,0,sizeof(person.firstName));
    item = cJSON_GetObjectItem(obiect,"firstName");
    memcpy(person.firstName,item->valuestring,strlen(item->valuestring));

    memset(person.lastName,0,sizeof(person.lastName));
    item = cJSON_GetObjectItem(obiect,"lastName");
    memcpy(person.lastName,item->valuestring,strlen(item->valuestring));

    memset(person.email,0,sizeof(person.email));
    item = cJSON_GetObjectItem(obiect,"email");
    memcpy(person.email,item->valuestring,strlen(item->valuestring));

    item = cJSON_GetObjectItem(obiect,"age");
    person.age = item->valueint;

    item = cJSON_GetObjectItem(obiect,"height");
    person.height = item->valuedouble;

    printf("firstname : %s\nlastname : %s\nemail : %s\nage : %d\nheight : %f\n",person.firstName,person.lastName,person.email,person.age,person.height);
    cJSON_Delete(root);
}

void cJSONTest3(PERSON worker[])
{ //解析结构体数组的JSON串
    char *data = "{\"people\":[  \
    {\"firstName\":\"z\",\"lastName\":\"Jason\",\"email\":\"bbbb@126.com\",\"height\":1.67},\
    {\"lastName\":\"jadena\",\"email\":\"jadena@126.com\",\"age\":8,\"height\":1.17},\
    {\"email\":\"cccc@126.com\",\"firstName\":\"z\",\"lastName\":\"Juliet\",\"age\":36,\"height\":1.55}]}";

    cJSON *root = cJSON_Parse(data);
    if(!root)return;

    cJSON *obiect = cJSON_GetObjectItem(root,"people");
    if(!obiect)return;

    int size = cJSON_GetArraySize(obiect);int i;


    for(i = 0;i < size;i++)
    {
        cJSON *arrayitem = cJSON_GetArrayItem(obiect,i);

        cJSON *item = cJSON_GetObjectItem(arrayitem,"firstName");
        if(item != NULL)
        {
            memset(worker[i].firstName,0,sizeof(worker[i].firstName));
            memcpy(worker[i].firstName,item->valuestring,strlen(item->valuestring));
            printf("worker[%d].firstName : %s\t",i,worker[i].firstName);
        }

        item = cJSON_GetObjectItem(arrayitem,"lastName");
        if(item != NULL)
        {
            memset(worker[i].lastName,0,sizeof(worker[i].lastName));
            memcpy(worker[i].lastName,item->valuestring,strlen(item->valuestring));
            printf("worker[%d].lastName : %s\t",i,worker[i].lastName);
        }

        item = cJSON_GetObjectItem(arrayitem,"email");
        if(item != NULL)
        {
            memset(worker[i].email,0,sizeof(worker[i].email));
            memcpy(worker[i].email,item->valuestring,strlen(item->valuestring));
            printf("worker[%d].email : %s\t",i,worker[i].email);
        }

        item = cJSON_GetObjectItem(arrayitem,"age");
        if(item != NULL)
        {
            worker[i].age = item->valueint;
            printf("worker[%d].age : %d\t",i,worker[i].age);
        }

        item = cJSON_GetObjectItem(arrayitem,"height");
        if(item != NULL)
        {
            worker[i].height = item->valuedouble;
            printf("worker[%d].height : %f\n",i,worker[i].height);
        }
    }

    cJSON_Delete(root);
    return ;
}

int main(void)
{
    PERSON worker[3];
    int i;
    cJSONTest3(worker);

    for(i = 0;i < 3;i++)
    {
        printf("i=%d,firstName=%s,lastName=%s,email=%s,age=%d,height=%f\n",i,worker[i].firstName,
               worker[i].lastName,worker[i].email,worker[i].age,worker[i].height);
    }
    return 0;
}
