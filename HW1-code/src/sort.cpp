#include "tweet.h"

void bubbleSort(std::vector<Tweet>& tweets, const std::string& sortBy, bool ascending) {
  int n = tweets.size();
  Tweet temp;

  if (sortBy == "tweetID"){

    if (ascending){
      for (size_t i = 0; i < n - 1; i++){
        for (size_t j = 0; j < n - 1 - i; j++){
          if (tweets[j].tweetID > tweets[j+1].tweetID){
            temp = tweets[j+1];
            tweets[j+1] = tweets[j];
            tweets[j] = temp;
          }
        }
      }

    } else{   // descending
      for (size_t i = 0; i < n - 1; i++){
        for (size_t j = 0; j < n - 1 - i; j++){
          if (tweets[j].tweetID < tweets[j+1].tweetID){
            temp = tweets[j+1];
            tweets[j+1] = tweets[j];
            tweets[j] = temp;
          }
        }
      }
    }
    
  } else if (sortBy == "retweetCount"){

    if (ascending){
      for (size_t i = 0; i < n - 1; i++){
        for (size_t j = 0; j < n - 1 - i; j++){
          if (tweets[j].retweetCount > tweets[j+1].retweetCount){
            temp = tweets[j+1];
            tweets[j+1] = tweets[j];
            tweets[j] = temp;
          }
        }
      }

    } else{   // descending
      for (size_t i = 0; i < n - 1; i++){
        for (size_t j = 0; j < n - 1 - i; j++){
          if (tweets[j].retweetCount < tweets[j+1].retweetCount){
            temp = tweets[j+1];
            tweets[j+1] = tweets[j];
            tweets[j] = temp;
          }
        }
      }
    }
    
  } else if (sortBy == "favoriteCount"){

    if (ascending){
      for (size_t i = 0; i < n - 1; i++){
        for (size_t j = 0; j < n - 1 - i; j++){
          if (tweets[j].favoriteCount > tweets[j+1].favoriteCount){
            temp = tweets[j+1];
            tweets[j+1] = tweets[j];
            tweets[j] = temp;
          }
        }
      }

    } else{   //descending
      for (size_t i = 0; i < n - 1; i++){
        for (size_t j = 0; j < n - 1 - i; j++){
          if (tweets[j].favoriteCount < tweets[j+1].favoriteCount){
            temp = tweets[j+1];
            tweets[j+1] = tweets[j];
            tweets[j] = temp;
          }
        }
      }
    }
    
  } else{
    std::cerr << "Wrong metric for bubbleSort()" << std::endl;
  }
}

void insertionSort(std::vector<Tweet>& tweets, const std::string& sortBy, bool ascending) {
  int n = tweets.size();
  Tweet key;

  if (sortBy == "tweetID"){

    if (ascending){
      for (size_t i = 1; i < n; i++){
        key = tweets[i];
        int j = i - 1;

        while (j >= 0 && tweets[j].tweetID > key.tweetID){
          tweets[j+1] = tweets[j];
          j--;
        }
        
        tweets[j+1] = key;
      }
      
    } else{   // descending
      for (size_t i = 1; i < n; i++){
        key = tweets[i];
        int j = i - 1;

        while (j >= 0 && tweets[j].tweetID < key.tweetID){
          tweets[j+1] = tweets[j];
          j--;
        }
        
        tweets[j+1] = key;
      }
    }
    
  } else if (sortBy == "retweetCount"){

    if (ascending){
      for (size_t i = 1; i < n; i++){
        key = tweets[i];
        int j = i - 1;

        while (j >= 0 && tweets[j].retweetCount > key.retweetCount){
          tweets[j+1] = tweets[j];
          j--;
        }
        
        tweets[j+1] = key;
      }

    } else{   // descending
      for (size_t i = 1; i < n; i++){
        key = tweets[i];
        int j = i - 1;

        while (j >= 0 && tweets[j].retweetCount < key.retweetCount){
          tweets[j+1] = tweets[j];
          j--;
        }
        
        tweets[j+1] = key;
      }
    }
    
  } else if (sortBy == "favoriteCount"){

    if (ascending){
      for (size_t i = 1; i < n; i++){
        key = tweets[i];
        int j = i - 1;

        while (j >= 0 && tweets[j].favoriteCount > key.favoriteCount){
          tweets[j+1] = tweets[j];
          j--;
        }
        
        tweets[j+1] = key;
      }
    } else{   // descending
      for (size_t i = 1; i < n; i++){
        key = tweets[i];
        int j = i - 1;

        while (j >= 0 && tweets[j].favoriteCount < key.favoriteCount){
          tweets[j+1] = tweets[j];
          j--;
        }
        
        tweets[j+1] = key;
      }
    }
    
  } else{
    std::cerr << "Wrong metric for insertionSort()" << std::endl;
  }
}

void merge(std::vector<Tweet>& tweets, int left, int mid, int right, const std::string& sortBy, bool ascending) {
  if (sortBy == "tweetID"){
    if (ascending){
      int n_left = mid - left + 1;
      int n_right = right - mid;

      std::vector<Tweet> left_arr, right_arr;

      // create left subarray
      for (size_t i = 0; i < n_left; i++){
        left_arr.push_back(tweets[left+i]);
      }
      // create right subarray
      for (size_t i = 0; i < n_right; i++){
        right_arr.push_back(tweets[mid+i+1]);
      }
      
      // merge
      int i = 0, j = 0;
      int k = left;

      while (i < n_left && j < n_right) {
        if (left_arr[i].tweetID <= right_arr[j].tweetID) {
            tweets[k] = left_arr[i];
            i++;
        } else {
            tweets[k] = right_arr[j];
            j++;
        }
        k++;
      }
      
      // since there are no sentinels to represent the end of the subarrays (requires additional library to import)
      // remaining elements of either one of the subarrays will be merged as en extra step
      while (i < n_left){
        tweets[k] = left_arr[i];
        k++;
        i++;
      }
      while (j < n_right){
        tweets[k] = right_arr[j];
        k++;
        j++;
      }
      
    } else{   // descending
      int n_left = mid - left + 1;
      int n_right = right - mid;

      std::vector<Tweet> left_arr, right_arr;

      // create left subarray
      for (size_t i = 0; i < n_left; i++){
        left_arr.push_back(tweets[left+i]);
      }
      // create right subarray
      for (size_t i = 0; i < n_right; i++){
        right_arr.push_back(tweets[mid+i+1]);
      }
      
      // merge
      int i = 0, j = 0;
      int k = left;

      while (i < n_left && j < n_right) {
        if (left_arr[i].tweetID >= right_arr[j].tweetID) {
            tweets[k] = left_arr[i];
            i++;
        } else {
            tweets[k] = right_arr[j];
            j++;
        }
        k++;
      }
      
      // since there are no sentinels to represent the end of the subarrays (requires additional library to import)
      // remaining elements of either one of the subarrays will be merged as en extra step
      while (i < n_left){
        tweets[k] = left_arr[i];
        k++;
        i++;
      }
      while (j < n_right){
        tweets[k] = right_arr[j];
        k++;
        j++;
      }
    }
    
  } else if (sortBy == "retweetCount"){
    if (ascending){
      int n_left = mid - left + 1;
      int n_right = right - mid;

      std::vector<Tweet> left_arr, right_arr;

      // create left subarray
      for (size_t i = 0; i < n_left; i++){
        left_arr.push_back(tweets[left+i]);
      }
      // create right subarray
      for (size_t i = 0; i < n_right; i++){
        right_arr.push_back(tweets[mid+i+1]);
      }
      
      // merge
      int i = 0, j = 0;
      int k = left;

      while (i < n_left && j < n_right) {
        if (left_arr[i].retweetCount <= right_arr[j].retweetCount) {
            tweets[k] = left_arr[i];
            i++;
        } else {
            tweets[k] = right_arr[j];
            j++;
        }
        k++;
      }
      
      // since there are no sentinels to represent the end of the subarrays (requires additional library to import)
      // remaining elements of either one of the subarrays will be merged as en extra step
      while (i < n_left){
        tweets[k] = left_arr[i];
        k++;
        i++;
      }
      while (j < n_right){
        tweets[k] = right_arr[j];
        k++;
        j++;
      }

    } else{   // descending
      int n_left = mid - left + 1;
      int n_right = right - mid;

      std::vector<Tweet> left_arr, right_arr;

      // create left subarray
      for (size_t i = 0; i < n_left; i++){
        left_arr.push_back(tweets[left+i]);
      }
      // create right subarray
      for (size_t i = 0; i < n_right; i++){
        right_arr.push_back(tweets[mid+i+1]);
      }
      
      // merge
      int i = 0, j = 0;
      int k = left;

      while (i < n_left && j < n_right) {
        if (left_arr[i].retweetCount >= right_arr[j].retweetCount) {
            tweets[k] = left_arr[i];
            i++;
        } else {
            tweets[k] = right_arr[j];
            j++;
        }
        k++;
      }
      
      // since there are no sentinels to represent the end of the subarrays (requires additional library to import)
      // remaining elements of either one of the subarrays will be merged as en extra step
      while (i < n_left){
        tweets[k] = left_arr[i];
        k++;
        i++;
      }
      while (j < n_right){
        tweets[k] = right_arr[j];
        k++;
        j++;
      }
    }
    
  } else if (sortBy == "favoriteCount"){
    if (ascending){
      int n_left = mid - left + 1;
      int n_right = right - mid;

      std::vector<Tweet> left_arr, right_arr;

      // create left subarray
      for (size_t i = 0; i < n_left; i++){
        left_arr.push_back(tweets[left+i]);
      }
      // create right subarray
      for (size_t i = 0; i < n_right; i++){
        right_arr.push_back(tweets[mid+i+1]);
      }
      
      // merge
      int i = 0, j = 0;
      int k = left;

      while (i < n_left && j < n_right) {
        if (left_arr[i].favoriteCount <= right_arr[j].favoriteCount) {
            tweets[k] = left_arr[i];
            i++;
        } else {
            tweets[k] = right_arr[j];
            j++;
        }
        k++;
      }
      
      // since there are no sentinels to represent the end of the subarrays (requires additional library to import)
      // remaining elements of either one of the subarrays will be merged as en extra step
      while (i < n_left){
        tweets[k] = left_arr[i];
        k++;
        i++;
      }
      while (j < n_right){
        tweets[k] = right_arr[j];
        k++;
        j++;
      }

    } else{   // descending
      int n_left = mid - left + 1;
      int n_right = right - mid;

      std::vector<Tweet> left_arr, right_arr;

      // create left subarray
      for (size_t i = 0; i < n_left; i++){
        left_arr.push_back(tweets[left+i]);
      }
      // create right subarray
      for (size_t i = 0; i < n_right; i++){
        right_arr.push_back(tweets[mid+i+1]);
      }
      
      // merge
      int i = 0, j = 0;
      int k = left;

      while (i < n_left && j < n_right) {
        if (left_arr[i].favoriteCount >= right_arr[j].favoriteCount) {
            tweets[k] = left_arr[i];
            i++;
        } else {
            tweets[k] = right_arr[j];
            j++;
        }
        k++;
      }
      
      // since there are no sentinels to represent the end of the subarrays (requires additional library to import)
      // remaining elements of either one of the subarrays will be merged as en extra step
      while (i < n_left){
        tweets[k] = left_arr[i];
        k++;
        i++;
      }
      while (j < n_right){
        tweets[k] = right_arr[j];
        k++;
        j++;
      }
    }
    
  }
}

void mergeSort(std::vector<Tweet>& tweets, int left, int right, const std::string& sortBy, bool ascending) {
  if (!(sortBy == "tweetID" || sortBy == "retweetCount" || sortBy == "favoriteCount")) {
    std::cerr << "Wrong metric for merge()" << std::endl;
    return;
  }
  
  int mid;
  if (left < right){
    mid = (left + right) / 2;
    mergeSort(tweets, left, mid, sortBy, ascending);
    mergeSort(tweets, mid + 1, right, sortBy, ascending);
    merge(tweets, left, mid, right, sortBy, ascending);
  }
}