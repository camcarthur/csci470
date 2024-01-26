# Use an official lightweight image of C++ runtime as a base image
FROM gcc:latest

# Set the working directory in the container
WORKDIR /usr/src/app

# Copy the current directory contents into the container at /usr/src/app
COPY . .

# Compile the C++ program
RUN g++ -o hello main.cpp

# Run the executable
CMD ["./hello"]
