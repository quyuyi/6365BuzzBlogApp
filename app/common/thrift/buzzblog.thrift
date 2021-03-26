// Copyright (C) 2020 Georgia Tech Center for Experimental Research in Computer
// Systems

namespace cpp gen
namespace py gen

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

struct TAccount {
  // Standard
  1: required i32 id;
  2: required i32 created_at;
  3: required bool active;
  4: required string username;
  5: required string first_name;
  6: required string last_name;

  // Expanded
  7: optional bool follows_you;
  8: optional bool followed_by_you;
  9: optional i32 n_followers;
  10: optional i32 n_following;
  11: optional i32 n_posts;
  12: optional i32 n_likes;
}

struct TFollow {
  // Standard
  1: required i32 id;
  2: required i32 created_at;
  3: required i32 follower_id;
  4: required i32 followee_id;

  // Expanded
  5: optional TAccount follower;
  6: optional TAccount followee;
}

struct TPost {
  // Standard
  1: required i32 id;
  2: required i32 created_at;
  3: required bool active;
  4: required string text;
  5: required i32 author_id;

  // Expanded
  6: optional TAccount author;
  7: optional i32 n_likes;
}

struct TLike {
  // Standard
  1: required i32 id;
  2: required i32 created_at;
  3: required i32 account_id;
  4: required i32 post_id;

  // Expanded
  5: required TAccount account;
  6: required TPost post;
}

struct TUniquepair {
  1: required i32 id;
  2: required i32 created_at;
  3: required string domain;
  4: required i32 first_elem;
  5: required i32 second_elem;
}


struct TRecPost {
  1: required i32 post_id;
  2: required string tweet_id;
  3: required i32 created_at;
  4: required string text;
  5: required list<string> keywords;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Exceptions
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

exception TAccountInvalidCredentialsException {
}

exception TAccountDeactivatedException {
}

exception TAccountInvalidAttributesException {
}

exception TAccountUsernameAlreadyExistsException {
}

exception TAccountNotFoundException {
}

exception TAccountNotAuthorizedException {
}

exception TFollowAlreadyExistsException {
}

exception TFollowNotFoundException {
}

exception TFollowNotAuthorizedException {
}

exception TLikeAlreadyExistsException {
}

exception TLikeNotFoundException {
}

exception TLikeNotAuthorizedException {
}

exception TPostInvalidAttributesException {
}

exception TPostNotFoundException {
}

exception TPostNotAuthorizedException {
}

exception TUniquepairNotFoundException {
}

exception TUniquepairAlreadyExistsException {
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Services
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

service TAccountService {
  /* Params:
   *   1. username: username to be verified.
   *   2. password: password to be verified.
   * Returns:
   *   An active account (standard mode) matching the provided credentials.
   */
  TAccount authenticate_user (1:string username, 2:string password)
      throws (1:TAccountInvalidCredentialsException e1,
              2:TAccountDeactivatedException e2);

  /* Params:
   *   1. username: username of the account to be created.
   *   2. password: password of the account to be created.
   *   3. first_name: first name of the account to be created.
   *   4. last_name: last name of the account to be created.
   * Returns:
   *   The newly created account (standard mode).
   */
  TAccount create_account (1:string username, 2:string password,
      3:string first_name, 4:string last_name)
      throws (1:TAccountInvalidAttributesException e1,
              2:TAccountUsernameAlreadyExistsException e2);

  /* Params:
   *   1. requester_id: id of the account making the request.
   *   2. account_id: id of the account to be retrieved.
   * Returns:
   *   The account (standard mode) matching the provided id.
   */
  TAccount retrieve_standard_account (1:i32 requester_id, 2:i32 account_id)
      throws (1:TAccountNotFoundException e);

  /* Params:
   *   1. requester_id: id of the account making the request.
   *   2. account_id: id of the account to be retrieved.
   * Returns:
   *   The account (expanded mode) matching the provided id.
   */
  TAccount retrieve_expanded_account (1:i32 requester_id, 2:i32 account_id)
      throws (1:TAccountNotFoundException e);

  /* Params:
   *   1. requester_id: id of the account making the request.
   *   2. account_id: id of the account to be updated.
   *   3. password: new password of the account to be updated.
   *   4. first_name: new first name of the account to be updated.
   *   5. last_name: new last name of the account to be updated.
   * Returns:
   *   The updated account (standard mode).
   */
  TAccount update_account (1:i32 requester_id, 2:i32 account_id,
      3:string password, 4:string first_name, 5:string last_name)
      throws (1:TAccountNotAuthorizedException e1,
              2:TAccountInvalidAttributesException e2,
              3:TAccountNotFoundException e3);

  /* Params:
   *   1. requester_id: id of the account making the request.
   *   2. account_id: id of the account to be deleted.
   */
  void delete_account (1:i32 requester_id, 2:i32 account_id)
      throws (1:TAccountNotAuthorizedException e1,
              2:TAccountNotFoundException e2);
}

service TFollowService {
  /* Params:
   *   1. requester_id: id of the account making the request.
   *   2. account_id: id of the account to be followed.
   * Returns:
   *   The newly created follow (standard mode).
   */
  TFollow follow_account (1:i32 requester_id, 2:i32 account_id)
      throws (1:TFollowAlreadyExistsException e);

  /* Params:
   *   1. requester_id: id of the account making the request.
   *   2. follow_id: id of the follow to be retrieved.
   * Returns:
   *   The follow (standard mode) matching the provided id.
   */
  TFollow retrieve_standard_follow (1:i32 requester_id, 2:i32 follow_id)
      throws (1:TFollowNotFoundException e);

  /* Params:
   *   1. requester_id: id of the account making the request.
   *   2. follow_id: id of the follow to be retrieved.
   * Returns:
   *   The follow (expanded mode) matching the provided id.
   */
  TFollow retrieve_expanded_follow (1:i32 requester_id, 2:i32 follow_id)
      throws (1:TFollowNotFoundException e1,
              2:TAccountNotFoundException e2);

  /* Params:
   *   1. requester_id: id of the account making the request.
   *   2. follow_id: id of the follow to be deleted.
   */
  void delete_follow (1:i32 requester_id, 2:i32 follow_id)
      throws (1:TFollowNotFoundException e1,
              2:TFollowNotAuthorizedException e2);

  /* Params:
   *   1. requester_id: id of the account making the request.
   *   2. follower_id: filter follows by id of the follower account. Any
   *                   negative value disables this filter.
   *   3. followee_id: filter follows by id of the followee account. Any
   *                   negative value disables this filter.
   * Returns:
   *   A list of follows (expanded mode) in reverse chronological order.
   */
  list<TFollow> list_follows (1:i32 requester_id, 2:i32 follower_id,
      3:i32 followee_id)
      throws (1:TAccountNotFoundException e);

  /* Params:
   *   1. requester_id: id of the account making the request.
   *   2. follower_id: id of the account to be checked as follower.
   *   3. followee_id: id of the account to be checked as followee.
   * Returns:
   *   True if follower follows followee. False, otherwise.
   */
  bool check_follow (1:i32 requester_id, 2:i32 follower_id, 3:i32 followee_id);

  /* Params:
   *   1. requester_id: id of the account making the request.
   *   2. account_id: id of the account whose followers are counted.
   * Returns:
   *   The number of followers of the provided account.
   */
  i32 count_followers (1:i32 requester_id, 2:i32 account_id);

  /* Params:
   *   1. requester_id: id of the account making the request.
   *   2. account_id: id of the account whose followees are counted.
   * Returns:
   *   The number of followees of the provided account.
   */
  i32 count_followees (1:i32 requester_id, 2:i32 account_id);
}

service TLikeService {
  /* Params:
   *   1. requester_id: id of the account making the request.
   *   2. post_id: id of the post to be liked.
   * Returns:
   *   The newly created like (standard mode).
   */
  TLike like_post (1:i32 requester_id, 2:i32 post_id)
      throws (1:TLikeAlreadyExistsException e);

  /* Params:
   *   1. requester_id: id of the account making the request.
   *   2. like_id: id of the like to be retrieved.
   * Returns:
   *   The like (standard mode) matching the provided id.
   */
  TLike retrieve_standard_like (1:i32 requester_id, 2:i32 like_id)
      throws (1:TLikeNotFoundException e);

  /* Params:
   *   1. requester_id: id of the account making the request.
   *   2. like_id: id of the like to be retrieved.
   * Returns:
   *   The like (expanded mode) matching the provided id.
   */
  TLike retrieve_expanded_like (1:i32 requester_id, 2:i32 like_id)
      throws (1:TLikeNotFoundException e1,
              2:TAccountNotFoundException e2,
              3:TPostNotFoundException e3);

  /* Params:
   *   1. requester_id: id of the account making the request.
   *   2. like_id: id of the like to be deleted.
   */
  void delete_like (1:i32 requester_id, 2:i32 like_id)
      throws (1:TLikeNotFoundException e1,
              2:TLikeNotAuthorizedException e2);

  /* Params:
   *   1. requester_id: id of the account making the request.
   *   2. account_id: filter likes by id of the account. Any negative value
   *                  disables this filter.
   *   3. post_id: filter likes by id of the post. Any negative value disables
   *               this filter.
   * Returns:
   *   A list of likes (expanded mode) in reverse chronological order.
   */
  list<TLike> list_likes (1:i32 requester_id, 2:i32 account_id,
      3:i32 post_id)
      throws (1:TAccountNotFoundException e1,
              2:TPostNotFoundException e2);

  /* Params:
   *   1. requester_id: id of the account making the request.
   *   2. account_id: id of the account whose likes are counted.
   * Returns:
   *   The number of likes by the provided account.
   */
  i32 count_likes_by_account (1:i32 requester_id, 2:i32 account_id);

  /* Params:
   *   1. requester_id: id of the account making the request.
   *   2. post_id: id of the post whose likes are counted.
   * Returns:
   *   The number of likes of the provided post.
   */
  i32 count_likes_of_post (1:i32 requester_id, 2:i32 post_id);
}

service TPostService {
  /* Params:
   *   1. requester_id: id of the account making the request.
   *   2. text: text of the post to be created.
   * Returns:
   *   The newly created post (standard mode).
   */
  TPost create_post (1:i32 requester_id, 2:string text)
      throws (1:TPostInvalidAttributesException e);

  /* Params:
   *   1. requester_id: id of the account making the request.
   *   2. post_id: id of the post to be retrieved.
   * Returns:
   *   The post (standard mode) matching the provided id.
   */
  TPost retrieve_standard_post (1:i32 requester_id, 2:i32 post_id)
      throws (1:TPostNotFoundException e);

  /* Params:
   *   1. requester_id: id of the account making the request.
   *   2. post_id: id of the post to be retrieved.
   * Returns:
   *   The post (expanded mode) matching the provided id.
   */
  TPost retrieve_expanded_post (1:i32 requester_id, 2:i32 post_id)
      throws (1:TPostNotFoundException e1,
              2:TAccountNotFoundException e2);

  /* Params:
   *   1. requester_id: id of the account making the request.
   *   2. post_id: id of the post to be deleted.
   */
  void delete_post (1:i32 requester_id, 2:i32 post_id)
      throws (1:TPostNotFoundException e1,
              2:TPostNotAuthorizedException e2);

  /* Params:
   *   1. requester_id: id of the account making the request.
   *   2. author_id: filter posts by id of the author account. Any negative
   *                 value disables this filter.
   * Returns:
   *   A list of posts (expanded mode) in reverse chronological order.
   */
  list<TPost> list_posts (1:i32 requester_id, 2:i32 author_id)
      throws (1:TAccountNotFoundException e);

  /* Params:
   *   1. requester_id: id of the account making the request.
   *   2. author_id: id of the author account whose posts are counted.
   * Returns:
   *   The number of posts written by the provided author account.
   */
  i32 count_posts_by_author (1:i32 requester_id, 2:i32 author_id);
}

service TUniquepairService {
  /* Params:
   *   1. uniquepair_id: id of the unique pair to be retrieved.
   * Returns:
   *   The unique pair matching the provided id.
   */
  TUniquepair get (1:i32 uniquepair_id)
      throws (1:TUniquepairNotFoundException e);

  /* Params:
   *   1. domain: domain of the unique pair to be added.
   *   2. first_elem: first element of the unique pair to be added.
   *   3. second_elem: second element of the unique pair to be added.
   * Returns:
   *   The newly created unique pair.
   */
  TUniquepair add (1:string domain, 2:i32 first_elem, 3:i32 second_elem)
      throws (1:TUniquepairAlreadyExistsException e);

  /* Params:
   *   1. uniquepair_id: id of the unique pair to be removed.
   */
  void remove (1:i32 uniquepair_id)
      throws (1:TUniquepairNotFoundException e);

  /* Params:
   *   1. domain: domain of the unique pair to be found.
   *   2. first_elem: first element of the unique pair to be found.
   *   3. second_elem: second element of the unique pair to be found.
   * Returns:
   *   The unique pair matching the provided elements.
   */
  TUniquepair find (1:string domain, 2:i32 first_elem, 3:i32 second_elem)
      throws (1:TUniquepairNotFoundException e);

  /* Params:
   *   1. domain: domain of the unique pairs to be listed.
   * Returns:
   *   A list of unique pairs in reverse chronological order.
   */
  list<TUniquepair> all (1:string domain);

  /* Params:
   *   1. domain: domain of the unique pairs to be listed.
   *   2. first_elem: first element of the unique pairs to be listed.
   * Returns:
   *   A list of unique pairs in reverse chronological order.
   */
  list<TUniquepair> filter_by_first_elem (1:string domain, 2:i32 first_elem);

  /* Params:
   *   1. domain: domain of the unique pairs to be listed.
   *   2. second_elem: second element of the unique pairs to be listed.
   * Returns:
   *   A list of unique pairs in reverse chronological order.
   */
  list<TUniquepair> filter_by_second_elem (1:string domain, 2:i32 second_elem);

  /* Params:
   *   1. domain: domain of the unique pairs to be counted.
   *   2. first_elem: first element of the unique pairs to be counted.
   * Returns:
   *   The number of unique pairs with the provided first element.
   */
  i32 count_first_elem (1:string domain, 2:i32 first_elem);

  /* Params:
   *   1. domain: domain of the unique pairs to be counted.
   *   2. second_elem: second element of the unique pairs to be counted.
   * Returns:
   *   The number of unique pairs with the provided second element.
   */
  i32 count_second_elem (1:string domain, 2:i32 second_elem);
}

////////////////////////////////////////////////////////////////////////////////
// Recommendation service
////////////////////////////////////////////////////////////////////////////////
service TRecommendationService {
  /* Params:
   *   1. keyword: filter posts by keyword
   *   2. search_size: limit the search space in the database
   *   3. return_size: limit the return size of the search results
   * Returns:
   *   A list of posts (standard mode) containing the keyword.
   */
  list<TRecPost> retrieve_recommended_posts (1:string keyword);
}