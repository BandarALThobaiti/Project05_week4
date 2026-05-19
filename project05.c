#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct FollowNode {
    char *follower; 
    int is_active;
    struct FollowNode *next;
} FollowNode;

typedef struct UserNode {
    char *username; 
    int followers_count;
    int unfollowers_count;
    FollowNode *followers_list;
    struct UserNode *next;
} UserNode;

UserNode *user_list = NULL;

UserNode *get_or_create_user(char *username) {
    UserNode *temp = user_list;
    
    while (temp != NULL) {
        if (strcmp(temp->username, username) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    
    UserNode *newUser = (UserNode *)malloc(sizeof(UserNode));
    newUser->username = strdup(username); 
    newUser->followers_count = 0;
    newUser->unfollowers_count = 0;
    newUser->followers_list = NULL;
    newUser->next = user_list;
    user_list = newUser;
    
    return newUser;
}

void follow(char *follower, char *followed) {
    UserNode *user = get_or_create_user(followed);
    FollowNode *temp = user->followers_list;
    
    while (temp != NULL) {
        if (strcmp(temp->follower, follower) == 0) {
            if (temp->is_active == 0) {
                temp->is_active = 1;
                user->followers_count++;
                user->unfollowers_count--;
            }
            return;
        }
        temp = temp->next;
    }
    
    FollowNode *newNode = (FollowNode *)malloc(sizeof(FollowNode));
    newNode->follower = strdup(follower); 
    newNode->is_active = 1;
    newNode->next = user->followers_list;
    user->followers_list = newNode;
    user->followers_count++;
}

void unfollow(char *follower, char *followed) {
    UserNode *user = get_or_create_user(followed);
    FollowNode *temp = user->followers_list;
    
    while (temp != NULL) {
        if (strcmp(temp->follower, follower) == 0 && temp->is_active == 1) {
            temp->is_active = 0;
            user->followers_count--;
            user->unfollowers_count++;
            return;
        }
        temp = temp->next;
    }
}

void print_user_stats(char *username) {
    UserNode *temp = user_list;
    
    while (temp != NULL) {
        if (strcmp(temp->username, username) == 0) {
            printf("%s Followers: %d\n", temp->username, temp->followers_count);
            printf("%s Unfollows: %d\n", temp->username, temp->unfollowers_count);
            printf("-------------------\n");
            return;
        }
        temp = temp->next;
    }
    printf("%s Followers: 0\n", username);
    printf("%s Unfollows: 0\n", username);
    printf("-------------------\n");
}

int main(void) {
    follow("Bandar", "Khalid");
    follow("Mohammed", "Khalid");
    follow("Ahmed", "Khalid");
    follow("Faisal", "Bandar");
    follow("Khalid", "Bandar");
    follow("Bandar", "Ahmed");
    follow("Mohammed", "Faisal");

    unfollow("Ahmed", "Khalid");
    unfollow("Faisal", "Bandar");

    print_user_stats("Khalid");
    print_user_stats("Bandar");
    print_user_stats("Ahmed");
    print_user_stats("Faisal");
    print_user_stats("Mohammed");

    return 0;
}