# Copyright (C) 2020 Georgia Tech Center for Experimental Research in Computer
# Systems

import time
import unittest

import requests
from requests.auth import HTTPBasicAuth


SERVER_HOSTNAME = "localhost"
SERVER_PORT = 8080 # url for api gateway
URL = "{hostname}:{port}".format(hostname=SERVER_HOSTNAME, port=SERVER_PORT)


class TestService(unittest.TestCase):
  # def test_create_account_200(self):
  #   r = requests.post("http://{url}/account".format(url=URL),
  #       json={
  #         "username": "john.doe",
  #         "password": "strongpasswd",
  #         "first_name": "John",
  #         "last_name": "Doe"
  #       }
  #   )
  #   self.assertEqual(200, r.status_code)
  #   response = r.json()
  #   self.assertEqual("account", response["object"])
  #   self.assertEqual("standard", response["mode"])
  #   self.assertIsInstance(response["id"], int)
  #   self.assertAlmostEqual(time.time(), response["created_at"], delta=60)
  #   self.assertTrue(response["active"])
  #   self.assertEqual("john.doe", response["username"])
  #   self.assertEqual("John", response["first_name"])
  #   self.assertEqual("Doe", response["last_name"])

  # TODO: Test the other API methods.

  def test_retrieve_recommended_posts(self):
    r = requests.get("http://{url}/recommendation/{keyword}".format(url=URL,keyword="good"),
        json={
          "search_size": 10,
          "return_size": 10
        }
    )
    self.assertEqual(200, r.status_code)
    response = r.json()
    print(response)

if __name__ == "__main__":
  unittest.main()
