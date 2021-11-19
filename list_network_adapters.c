// Copyright 2021 kkozlov

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>

int list_network_adapters();

int main(int argc, char **argv)
{
  return list_network_adapters();
}

int list_network_adapters()
{
  struct ifaddrs *addrs;
  if (getifaddrs(&addrs)) {
    printf("getifaddrs call failed\n");
    return -1;
  }
  struct ifaddrs *it = addrs;
  while (it) {
    int family = it->ifa_addr->sa_family;
    if (AF_INET == family || AF_INET6 == family) {
      printf("%-10s\t", it->ifa_name);
      printf("%-10s\t", family == AF_INET ? "IPv4" : "IPv6");
      char buf[128];
      int const family_size = AF_INET == family ?
          sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6);
      getnameinfo(it->ifa_addr, family_size, buf, sizeof(buf), 0, 0,
                  NI_NUMERICHOST);
      printf("%-s\n", buf);
    }
    it = it->ifa_next;
  }
  return EXIT_SUCCESS;
}
