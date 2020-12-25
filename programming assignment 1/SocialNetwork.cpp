#include "SocialNetwork.h"

#include <iostream>

SocialNetwork::SocialNetwork() {

}

void SocialNetwork::addProfile(const std::string &firstname, const std::string &lastname, const std::string &email) {
    /* TODO */
    Profile new_profile(firstname, lastname, email);
    
    profiles.insertSorted(new_profile);
}

void SocialNetwork::addPost(const std::string &message, const std::string &email) {
    /* TODO */
    Post new_post(message);
    Node<Profile> *temp = profiles.getFirstNode();
    
    posts.insertAtTheTail(new_post);
    
    while (temp)
    {
        if (temp->data.getEmail() == email)
        {
            temp->data.getPosts().insertAtTheTail(&(posts.getLastNode()->data));
            break;
        }
        temp = temp->next;
    }
}

void SocialNetwork::deleteProfile(const std::string &email) {
    /* TODO */
    Node<Profile> *temp_profile = profiles.getFirstNode();

    while (temp_profile)
    {
        if (temp_profile->data.getEmail() == email)
        {
            Node<Profile> *all_users = profiles.getFirstNode();
            Node<Post *> *profile_posts = temp_profile->data.getPosts().getFirstNode();
            Node<Profile *> *profile_friends = temp_profile->data.getFriends().getFirstNode();
            
            while (profile_friends)
            {
                profile_friends->data->dropFriend(&(temp_profile->data));
                profile_friends = profile_friends->next;
            }
            
            while (profile_posts)
            {
                while (all_users)
                {
                    all_users->data.dropLike(profile_posts->data);
                    all_users = all_users->next;
                }
                posts.removeNode(*(profile_posts->data));
                profile_posts = profile_posts->next;
            }
            break;
        }
        temp_profile = temp_profile->next;
    }
    
    temp_profile->data.getLikes().removeAllNodes();
    temp_profile->data.getPosts().removeAllNodes();
    temp_profile->data.getFriends().removeAllNodes();
    profiles.removeNode(temp_profile);
}

void SocialNetwork::makeFriends(const std::string &email1, const std::string &email2) {
    /* TODO */
    Node<Profile> *friend1;
    Node<Profile> *friend2;
    Node<Profile> *temp = profiles.getFirstNode();
    
    while (temp)
    {
        if (temp->data.getEmail() == email1)
        {
            friend1 = temp;
        }
        else if (temp->data.getEmail() == email2)
        {
            friend2 = temp;
        }
        temp = temp->next;
    }
    
    friend1->data.addFriend(&(friend2->data));
    friend2->data.addFriend(&(friend1->data));
}

void SocialNetwork::likePost(int postId, const std::string &email) {
    /* TODO */
    Node<Profile> *temp = profiles.getFirstNode();
    Node<Post> *temp_posts = posts.getFirstNode();
    
    while (temp_posts)
    {
        if (temp_posts->data.getPostId() == postId)
        {
            while (temp)
            {
                if (temp->data.getEmail() == email)
                {
                    temp->data.addLike(&(temp_posts->data));
                    break;
                }
                temp = temp->next;
            }
        }
        temp_posts = temp_posts->next;
    }
}

void SocialNetwork::unlikePost(int postId, const std::string &email) {
    /* TODO */
    Node<Profile> *temp = profiles.getFirstNode();
    Node<Post> *temp_posts = posts.getFirstNode();
    
    while (temp_posts)
    {
        if (temp_posts->data.getPostId() == postId)
        {
            while (temp)
            {
                if (temp->data.getEmail() == email)
                {
                    temp->data.dropLike(&(temp_posts->data));
                    break;
                }
                temp = temp->next;
            }
        }
        temp_posts = temp_posts->next;
    }
}

LinkedList<Profile *> SocialNetwork::getMutualFriends(const std::string &email1, const std::string &email2) {
    /* TODO */
    LinkedList<Profile *> *mutual_friends = new LinkedList<Profile *>();
    Node<Profile> *friend1;
    Node<Profile> *friend2;
    Node<Profile> *temp = profiles.getFirstNode();
    
    while (temp)
    {
        if (temp->data.getEmail() == email1)
        {
            friend1 = temp;
        }
        else if (temp->data.getEmail() == email2)
        {
            friend2 = temp;
        }
        temp = temp->next;
    }
    
    Node<Profile *> *friends_list1 = friend1->data.getFriends().getFirstNode();
    
    while (friends_list1)
    {
        Node<Profile *> *friends_list2 = friend2->data.getFriends().getFirstNode();
        
        while(friends_list2)
        {
            if (friends_list1->data == friends_list2->data)
            {
                mutual_friends->insertAtTheTail(friends_list1->data);
                friends_list2 = friends_list2->next;
            }
            friends_list1 = friends_list1->next;
        }
    }
    
    return *mutual_friends;
}

LinkedList<Post *> SocialNetwork::getListOfMostRecentPosts(const std::string &email, int k) {
    /* TODO */
    LinkedList<Post *> *recent_posts;
    Node<Profile> *temp = profiles.getFirstNode();
    int i, num_of_posts;
    
    while (temp)
    {
        if (temp->data.getEmail() == email)
        {
            Node<Post *> *temp_post = temp->data.getPosts().getLastNode();
            num_of_posts = temp->data.getPosts().getNumberOfNodes();
            
            if (k < num_of_posts)
            {
                for (i = 0; i < k && temp_post; i++)
                {
                    recent_posts->insertAtTheTail(temp_post->data);
                    temp_post = temp_post->prev;
                }
            }
        }
        temp = temp->next;
    }
    return *recent_posts;
}

void SocialNetwork::print() const {
    std::cout << "# Printing the social network ..." << std::endl;

    std::cout << "# Number of profiles is " << profiles.getNumberOfNodes() << ":" << std::endl;
    profiles.print();

    std::cout << "# Number of posts is " << posts.getNumberOfNodes() << ":" << std::endl;
    posts.print();

    std::cout << "# Printing is done." << std::endl;
}
