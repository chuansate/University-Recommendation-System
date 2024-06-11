# University Recommendation System
The Ministry of Higher Education (MoHE) will be holding several education exhibitions in 
Malaysia soon. To support these education exhibitions, they plan to develop a smart 
recommendation system to help parents of secondary school students better understanding the 
quality of universities around the world and make it easier to plan a better future education for 
their children. 

As one of MoHE's partners, your company intends to participate in the development part of the 
above system. A *2023 QS University Rankings dataset* will be used in this system. This dataset 
contains information of more than 1400 different universities from all over the world. It also 
includes several attributes such as the institution’s name, location, and various sub-scores in 
different fields, as well as the ranks of the universities. The details of the columns as below: 
• ar (academic reputation) 
• er (employer reputation) 
• fsr (faculty/student ratio) 
• cpf (citations per faculty) 
• ifr (international faculty ratio) 
• isr (international student ratio) 
• irn (international research network) 
• ger (employment outcome) 

Suppose you are one of the software developers in the company, your supervisor has assigned 
you to develop this system with THREE (3) other employees. Your team must develop it in 
C++ programming and implement appropriate data structures to store and manage different 
types of information in the system, e.g. university details, user's personal details, user's favorite 
university, etc. 

The system contains the following functionalities: 

**Normal Users**
- Display all the universities’ information from the dataset. 
- Sort university information in ascending order by university name.
  - Apply 2 distinct sort algorithms in this function to compare their execution time. 
- Search individual university details.  
  - Apply 2 distinct search algorithms in this function to compare their execution time. 
- Register as customer of the education exhibition.


**Registered Users (Customer)**
- Login and logout. 
- Sort university information in descending order based on academic reputation score, 
faculty/student ratio score and employer reputation score. 
- Search universities details based on customer decision. 
- Save their favorite universities. 
- Send feedback to MoHE for further information about the University. 
- Read the feedback reply from the MoHE based on latest date.


**MoHE admin**
- Login and logout. 
- Display all registered users’ details. 
- Modify a user detail. 
- Delete user accounts based on inactivity status. 
- Move back and forth between the feedback of registered users according to the latest 
date. 
- Reply to the registered user’s feedback. 
- Based on the list of all customers' favorite universities, summarize the top 10 
universities most preferred by parents in Malaysia and generate a report. 
