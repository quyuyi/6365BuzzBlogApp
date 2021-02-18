# Copyright (C) 2020 Georgia Tech Center for Experimental Research in Computer
# Systems

import time
import unittest

from buzzblog.gen.ttypes import *
from buzzblog.follow_client import Client as FollowClient


IP_ADDRESS = "localhost"
PORT = 9092


class TestService(unittest.TestCase):
  def test_follow_account_and_retrieve_standard_follow(self):
    with FollowClient(IP_ADDRESS, PORT) as client:
      # Follow an account and check the returned object's attributes.
      follow = client.follow_account(1, 2)
      self.assertAlmostEqual(time.time(), follow.created_at, delta=60)
      self.assertEqual(1, follow.follower_id)
      self.assertEqual(2, follow.followee_id)
      # Retrieve that follow and check its attributes.
      retrieved_follow = client.retrieve_standard_follow(1, follow.id)
      self.assertEqual(follow.id, retrieved_follow.id)
      self.assertEqual(follow.created_at, retrieved_follow.created_at)
      self.assertEqual(follow.follower_id, retrieved_follow.follower_id)
      self.assertEqual(follow.followee_id, retrieved_follow.followee_id)

  def test_retrieve_expanded_follow(self):
    # TODO
    pass

  def test_delete_follow(self):
    # TODO
    pass

  def test_list_follows(self):
    # TODO
    pass

  def test_check_follow(self):
    # TODO
    pass

  def test_count_followers(self):
    # TODO
    pass

  def test_count_followees(self):
    # TODO
    pass


if __name__ == "__main__":
  unittest.main()
