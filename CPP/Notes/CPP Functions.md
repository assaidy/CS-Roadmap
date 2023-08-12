In computer programming, a function is a self-contained block of code that performs a specific task. It is a fundamental building block of [[procedural and structured programming]]. Functions allow you to break down a program into smaller, manageable units, each responsible for a specific functionality. They promote code reusability, modularity, and maintainability. Functions promote a famous approach called **DRY** (don't repeat your self)

### Syntax
```cpp
return_type function_name(parameters){
	function_body;
}
```

Example
```cpp
int add(int a, int b){
	return a + b;
}
```

when a function does not return any thing, it's return type is `void`
```cpp
void print_hello(std::string name){
	std::cout << "hello, " << name << '\n';
}
```

### Declaration, definition and prototype
```cpp
// Function prototype and the definition is after main()
int multiply(int a, int b);

// Function definition before main()
int add(int a, int b) {
    return a + b;
}

int main() {
    int result1 = add(3, 4);
    // Output: 7
    int result2 = multiply(3, 4);
    // Output: 12
	
    return 0;
}

// Function Definition after main()
int multiply(int a, int b){
	return a * b;
}
```

> It's a good practice to follow the function prototype approach. 

### Regular and Default argument
```cpp
// Function with a regular argument
void greetPerson(std::string name) {
	std::cout << "Hello, " << name << "!" << std::endl;
}

// Function with a default argument
void printMessage(std::string name{"User"}) {
	std::cout << "Hello, " << name << "!" << std::endl;
}
// printMessage("Ahmad");
// Hello, Ahmad!

// printMessage();
// Hello, User!
```

*you should add the default parameter from the last to first:*
```cpp
void print_data(std::string fName, std::string lName = "Alsaidy", int age = 20) {
    std::cout << fName << ' ' << lName << ", " << age << '\n';
}
// Compiled Successfully

void print_data(std::string fName, std::string lName, int age = 20) {
    std::cout << fName << ' ' << lName << ", " << age << '\n';
}
// Compiled Successfully

void print_data(std::string fName, std::string lName = "Alsaidy", int age) {
    std::cout << fName << ' ' << lName << ", " << age << '\n';
}
// Error

void print_data(std::string fName = "Ahmad", std::string lName, int age) {
    std::cout << fName << ' ' << lName << ", " << age << '\n';
}
// Error
```

