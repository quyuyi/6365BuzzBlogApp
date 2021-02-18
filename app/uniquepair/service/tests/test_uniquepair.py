# Copyright (C) 2020 Georgia Tech Center for Experimental Research in Computer
# Systems

import time
import unittest

from buzzblog.gen.ttypes import *
from buzzblog.uniquepair_client import Client as UniquepairClient


IP_ADDRESS = "localhost"
PORT = 9095


class TestService(unittest.TestCase):
  def test_add_and_get(self):
    with UniquepairClient(IP_ADDRESS, PORT) as client:
      # Add uniquepair and check its attributes.
      uniquepair = client.add("test_add_and_get", 1, 2)
      self.assertEqual("test_add_and_get", uniquepair.domain)
      self.assertAlmostEqual(time.time(), uniquepair.created_at, delta=60)
      self.assertEqual(1, uniquepair.first_elem)
      self.assertEqual(2, uniquepair.second_elem)
      # Get that uniquepair and check its attributes.
      gotten_uniquepair = client.get(uniquepair.id)
      self.assertEqual(uniquepair.id, gotten_uniquepair.id)
      self.assertEqual(uniquepair.created_at,
          gotten_uniquepair.created_at)
      self.assertEqual(uniquepair.domain, gotten_uniquepair.domain)
      self.assertEqual(uniquepair.first_elem,
          gotten_uniquepair.first_elem)
      self.assertEqual(uniquepair.second_elem,
          gotten_uniquepair.second_elem)

  def test_remove(self):
    with UniquepairClient(IP_ADDRESS, PORT) as client:
      # Add uniquepair.
      uniquepair = client.add("test_remove", 1, 2)
      # Remove that uniquepair and check that it cannot be gotten anymore.
      client.remove(uniquepair.id)
      with self.assertRaises(TUniquepairNotFoundException):
        client.get(uniquepair.id)

  def test_find(self):
    # TODO
    pass

  def test_all(self):
    # TODO
    pass

  def test_filter_by_first_elem(self):
    # TODO
    pass

  def test_filter_by_second_elem(self):
    # TODO
    pass

  def test_count_first_elem(self):
    # TODO
    pass

  def test_count_second_elem(self):
    # TODO
    pass


if __name__ == "__main__":
  unittest.main()
