# Vending Machine System  

Aidan Munns and Livy Bottomley

Our Vending Machine System was designed to address the problem of students on college campuses not having easy access to quick snack options while studying. The existing food locations on campus are often far away from study areas, which results in inconvenient, time-consuming breaks. This disrupts their study flow, making it harder to stay focused. By creating an easy-to-use vending system that can be accessed quickly, this project aims to help students get the food and energy they need without breaking their concentration.

In this project, we used a matrix keypad for input, an LCD for feedback, and servos for dispensing snacks, ensuring a smooth and quick user experience for this system. Additionally, the system includes LED indicators for transaction feedback and motion sensors to verify snack dispensing.

# System Components  

| Component                     | Description                                        |
|-----------------------|------------------------------------------------------------|
| **Matrix Keypad**     | Allows user to select snack choice and payment             |
| **LCD Display**       | Displays current transaction information                   |
| **Green LED**         | Lights up when a valid item is chosen or payment made      |
| **Red LED**           | Lights up when an invalid item is chosen or payment made   |
| **Continuous Servos** | Rotate to release the selected snack from shelf            |
| **Positional Servo**  | Opens and closes the door                                  |
| **PIR Sensor**        | Detects motion to trigger the door opening                 |
| **RGB LED**           | Visually lights up the system                              |


# Testing Results  

| Subsystem                 | Specification                                                                                 | Results  | 
|---------------------------|-----------------------------------------------------------------------------------------------|----------|
| **Dispenser System**      | Enable the snack to be dispensed after successful payment                                     |  Pass    |
|                           | Activate continuous servo for left/right dispensing based on item                             |  Pass    |
|                           | Activate positional servo when motion sensed                                                  |  Pass    |                         
| **Payment System**        | Verifies payment is successful when valid ID is entered                                       |  Pass    |
|                           | Ensures red LED turns on and error message displayed if payment invalid                       |  Pass    |
|                           | Ensures green LED turns on and message displayed if payment is valid                          |  Pass    |
|                           | Allows for multiple attempts if payment is invalid                                            |  Pass    |
| **Item Selection System** | Checks item that has been selected is a valid one                                             |  Pass    |
|                           | Ensures red LED turns on and error message displayed if chosen snack is invalid               |  Pass    |
|                           | Ensures green LED turns on and success message displayed if chosen snack is valid             |  Pass    |
| **User Interface System** | Ensures the user is greeted with a welcome message                                            |  Pass    |
|                           |Ensures the keypad input updates to the display correctly                                      |  Pass    |
|                           | Handles display changes based on current transaction state                                    |  Pass    |  
|                           | Ensures transaction state progresses from welcome to item selection to payment to dispensing  |  Pass    |
|                           | Ensures there is a rest in the system after successful dispensing                             |  Pass    |
|                           | Allows repeated use (system resets after transaction complete)                                |  Pass    |





