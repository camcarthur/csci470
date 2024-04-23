# set base image 
FROM ubuntu:22.04

# install packages for acls and user management
RUN apt-get update && apt-get install -y acl && apt-get install -y bash

# create the user, their home dir, setting shell to
# bash, and create group
RUN useradd -m myuser && groupadd mygroup

# make the file system
RUN mkdir /filesystem

# set ownership of /filesystem dir to myuser and my group
RUN chown myuser:mygroup /filesystem

# configure the access control lists for the filesystem
# permissions we are setting is 760
RUN setfacl -m u:myuser:rwx /filesystem
RUN setfacl -m g:mygroup:rw /filesystem
RUN setfacl -d -m u:myuser:rwx /filesystem
RUN setfacl -d -m g:mygroup:rw /filesystem

# start bash shell by default
CMD [ "/bin/bash" ]