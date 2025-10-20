package main

import (
	"bufio"
	"encoding/gob"
	"fmt"
	"math/rand"
	"os"
	"strings"
	"time"
)

const (
	NumSubjects     = 7
	MaxNameLen      = 30
	DBFile          = "students.dat"
	DegreesFile     = "degrees.txt"
	MaxNameLength   = 100
	StudentPassword = 1000
	DoctorReg       = 2000
	DoctorPass      = 2000
	LecturerReg     = 3000
	LecturerPass    = 3000
)

type Student struct {
	REG  int
	Name string
	Age  int
	GPA  float64
}

type Degree struct {
	RegisterNumber string
	Subject        string
	Week7          int
	Week12         int
	Coursework     int
	Final          int
}

func main() {
	rand.Seed(time.Now().UnixNano())
	start()
}

func start() {
	for {
		clearScreen()
		fmt.Println("\n\n\t\t\t\t\t===== WELCOME TO OUR PROJECT =====\t\t\t")
		fmt.Println("\n\n\n\t\t\t1) Student\t\t2) Doctor\t\t3) Lecturer\t\t4) Exit\n")

		var choice int
		fmt.Scan(&choice)

		switch choice {
		case 1:
			clearScreen()
			studentPortal()
		case 2:
			clearScreen()
			doctorPortal()
		case 3:
			clearScreen()
			lecturerPortal()
		case 4:
			clearScreen()
			fmt.Println("\n\t\t\t\tTHANKS FOR USING OUR SOFTWARE\n")
			os.Exit(0)
		default:
			fmt.Println("Invalid choice. Please try again.")
			pause()
		}
	}
}

func studentPortal() {
	fmt.Println("\n\n\t\t\t\t\t======STUDENT PORTAL======\t\t\t")

	var sm, t12, reg, pass int

	clearScreen()
	fmt.Print("\t\t\t\n\n\nAre you majoring in 1) Science  2) Mathematics: ")
	fmt.Scan(&sm)
	fmt.Print("\t\t\t\n\n\nAre you 1) [TERM 1] OR 2) [TERM 2]: ")
	fmt.Scan(&t12)
	fmt.Print("\t\t\t\n\n\nEnter your registration number: ")
	fmt.Scan(&reg)
	fmt.Print("\t\t\t\n\n\nEnter your PASSWORD: ")
	fmt.Scan(&pass)

	clearScreen()

	// Load students from file
	students, err := loadStudents()
	if err != nil {
		fmt.Println("Error: Unable to open database file.")
		pause()
		return
	}

	found := false
	var student Student
	for _, s := range students {
		if s.REG == reg && pass == StudentPassword {
			found = true
			student = s
			break
		}
	}

	if !found {
		fmt.Println("Invalid credentials. Press any key to continue...")
		pause()
		clearScreen()
		return
	}

	// Student menu loop
	for {
		clearScreen()
		fmt.Println("\n\n\n\t\t\t\t1- Show Result")
		fmt.Println("\t\t\t\t2- Show Attendance")
		fmt.Println("\t\t\t\t3- Show my Weekly Table of Courses")
		fmt.Println("\t\t\t\t4- Show my information")
		fmt.Println("\t\t\t\t5- Calculate GPA")
		fmt.Println("\t\t\t\t6- EXIT")
		fmt.Println("\t\t\t\t__________________________________________")

		var op int
		fmt.Scan(&op)
		clearScreen()

		switch op {
		case 1:
			showResults(sm, t12)
		case 2:
			showAttendance(sm)
		case 3:
			showTimetable(sm, t12)
		case 4:
			showStudentInfo(student)
		case 5:
			calculateGPA()
		case 6:
			return
		default:
			fmt.Println("Invalid option.")
		}

		fmt.Println("\n\t\t\t\tPress Enter to continue...")
		pause()
	}
}

func showResults(sm, t12 int) {
	var op2 int

	if t12 == 2 {
		fmt.Println("\n1 - Show my Current Result")
		fmt.Println("2 - Show my Semester September 2022 Result")
	} else {
		fmt.Println("\n1 - Show my Current Result")
	}

	fmt.Scan(&op2)
	clearScreen()

	if sm == 2 { // Mathematics
		if op2 == 1 {
			displayCourseTableMath1()
		} else if op2 == 2 {
			displayCourseTableMath2()
		}
	} else if sm == 1 { // Science
		if op2 == 1 {
			displayCourseTableScience1()
		} else if op2 == 2 {
			displayCourseTableScience2()
		}
	}
}

func showAttendance(sm int) {
	if sm == 2 {
		displayAttendanceMath()
	} else if sm == 1 {
		displayAttendanceScience()
	}
}

func showTimetable(sm, t12 int) {
	if sm == 2 {
		displayTimetableMath()
	} else if sm == 1 {
		if t12 == 1 {
			displayTimetableScience1()
		} else if t12 == 2 {
			displayTimetableScience2()
		}
	}
}

func showStudentInfo(s Student) {
	fmt.Println("+----------------------+------------------+")
	fmt.Println("|     Information      |     Details      |")
	fmt.Println("+----------------------+------------------+")
	fmt.Printf("| Name                 |  %-15s |\n", s.Name)
	fmt.Printf("| REG number           |  %-15d |\n", s.REG)
	fmt.Printf("| GPA                  |  %-15.2f |\n", s.GPA)
	fmt.Printf("| Age                  |  %-15d |\n", s.Age)
	fmt.Println("+----------------------+------------------+")
}

func calculateGPA() {
	fmt.Println("\t\t\t\t\t\t\t======Student GPA======\n\n\n\t\t\t")
	fmt.Println("\tA+ =====> ( 96 )\tA  =====> ( 94 )\tA- =====> ( 90 )\n\n\n\t\t\t")
	fmt.Println("\tB+ =====> ( 86 )\tB  =====> ( 82 )\tB- =====> ( 78 )\n\n\n\t\t\t")
	fmt.Println("\tC+ =====> ( 74 )\tC  =====> ( 70 )\tC- =====> ( 66 )\n\n\n\t\t\t")
	fmt.Println("\tD+ =====> ( 62 )\tD  =====> ( 57 )\tD- =====> ( 52 ) \n\n\n\t\t\t")

	var numCourses int
	fmt.Print("Enter the number of courses: ")
	fmt.Scan(&numCourses)

	marks := make([]int, numCourses)
	totalMarks := 0

	for i := 0; i < numCourses; i++ {
		fmt.Printf("\n\n\t\t\t\tEnter marks of course %d: ", i+1)
		fmt.Scan(&marks[i])
		totalMarks += marks[i]
	}

	avg := float64(totalMarks) / float64(numCourses)
	fmt.Printf("\n\n\t\t\t\tYour average = %.2f\n", avg)

	fmt.Println("\n\n\t\t\t___________________________________________________________________")

	var gpa float64
	var grade string

	switch {
	case avg >= 96:
		gpa, grade = 4.0, "A+"
	case avg >= 92:
		gpa, grade = 3.7, "A"
	case avg >= 88:
		gpa, grade = 3.4, "A-"
	case avg >= 84:
		gpa, grade = 3.2, "B+"
	case avg >= 80:
		gpa, grade = 3.0, "B"
	case avg >= 76:
		gpa, grade = 2.8, "B-"
	case avg >= 72:
		gpa, grade = 2.6, "C+"
	case avg >= 68:
		gpa, grade = 2.4, "C"
	case avg >= 64:
		gpa, grade = 2.2, "C-"
	case avg >= 60:
		gpa, grade = 2.0, "D+"
	case avg >= 55:
		gpa, grade = 1.5, "D"
	case avg >= 50:
		gpa, grade = 1.0, "D-"
	default:
		gpa, grade = 0.0, "F"
	}

	fmt.Printf("\n\n\t\t\t\tYou got a GPA = %.1f\n", gpa)
	fmt.Printf("\t\t\t\t\t\t\t\t\t\tYour grade is: %s\n\n", grade)
}

func doctorPortal() {
	var regck, passck int

	for {
		clearScreen()
		fmt.Println("\n\n\t\t\t\t\t======DOCTOR PORTAL======\t\t\t")
		fmt.Print("\n\n\nEnter USER: ")
		fmt.Scan(&regck)
		fmt.Print("\n\n\nEnter password: ")
		fmt.Scan(&passck)
		clearScreen()

		if regck == DoctorReg && passck == DoctorPass {
			break
		} else {
			fmt.Println("\t\t\t\t\t\n\n\nWrong pass or Reg. Please try again.\n\t\t\t")
			pause()
		}
	}

	for {
		clearScreen()
		fmt.Println("\n\n\t\t\t\t\t======University Doctor - Degrees Management======\t\t\t")
		fmt.Println("\n\n\n\t\t\t\t1- Add Degrees")
		fmt.Println("\t\t\t\t2- Edit Degrees")
		fmt.Println("\t\t\t\t3- Quit")
		fmt.Println("\t\t\t\t__________________________________________")

		var choice int
		fmt.Scan(&choice)
		clearScreen()

		switch choice {
		case 1:
			addDegrees()
		case 2:
			editDegrees()
		case 3:
			return
		default:
			fmt.Println("Invalid choice. Please try again.")
			pause()
		}
	}
}

func lecturerPortal() {
	var rego, passo int

	for {
		clearScreen()
		fmt.Println("\n\n\t\t\t\t\t===== LECTURER PORTAL =====\t\t\t")
		fmt.Print("\n\nEnter USER: ")
		fmt.Scan(&rego)
		fmt.Print("\n\nEnter password: ")
		fmt.Scan(&passo)
		clearScreen()

		if rego == LecturerReg && passo == LecturerPass {
			break
		} else {
			fmt.Println("Wrong pass or Reg. Please try again.")
			pause()
		}
	}

	for {
		clearScreen()
		fmt.Println("\n\n\n\t\t\t\t1- Add student")
		fmt.Println("\t\t\t\t2- Edit student")
		fmt.Println("\t\t\t\t3- Search for student")
		fmt.Println("\t\t\t\t4- Exit")
		fmt.Println("\t\t\t\t__________________________________________")

		var choice int
		fmt.Scan(&choice)
		clearScreen()

		switch choice {
		case 1:
			addStudent()
		case 2:
			editStudent()
		case 3:
			searchStudent()
		case 4:
			return
		default:
			fmt.Println("Invalid choice.")
		}

		fmt.Println("\n\t\t\t\tPress Enter to continue...")
		pause()
	}
}

func addStudent() {
	var s Student

	fmt.Print("Enter student Reg: ")
	fmt.Scan(&s.REG)
	fmt.Print("Enter student name: ")
	reader := bufio.NewReader(os.Stdin)
	s.Name, _ = reader.ReadString('\n')
	s.Name = strings.TrimSpace(s.Name)
	fmt.Print("Enter student age: ")
	fmt.Scan(&s.Age)
	fmt.Print("Enter student GPA: ")
	fmt.Scan(&s.GPA)

	students, _ := loadStudents()
	students = append(students, s)

	err := saveStudents(students)
	if err != nil {
		fmt.Println("Error: Unable to save student.")
		return
	}

	fmt.Println("Student added successfully.")
}

func editStudent() {
	var reg int
	fmt.Print("Enter student ID to edit: ")
	fmt.Scan(&reg)

	students, err := loadStudents()
	if err != nil {
		fmt.Println("Error: Unable to open database file.")
		return
	}

	found := false
	for i, s := range students {
		if s.REG == reg {
			found = true

			reader := bufio.NewReader(os.Stdin)
			fmt.Print("Enter new student name: ")
			students[i].Name, _ = reader.ReadString('\n')
			students[i].Name = strings.TrimSpace(students[i].Name)
			fmt.Print("Enter new student age: ")
			fmt.Scan(&students[i].Age)
			fmt.Print("Enter new student GPA: ")
			fmt.Scan(&students[i].GPA)

			saveStudents(students)
			fmt.Println("Student record updated successfully.")
			break
		}
	}

	if !found {
		fmt.Printf("Error: Student with REG %d not found.\n", reg)
	}
}

func searchStudent() {
	var reg int
	fmt.Print("Enter student ID to search for: ")
	fmt.Scan(&reg)

	students, err := loadStudents()
	if err != nil {
		fmt.Println("Error: Unable to open database file.")
		return
	}

	found := false
	for _, s := range students {
		if s.REG == reg {
			found = true
			showStudentInfo(s)
			break
		}
	}

	if !found {
		fmt.Printf("Error: Student with REG %d not found.\n", reg)
	}
}

func addDegrees() {
	clearScreen()

	var degree Degree
	reader := bufio.NewReader(os.Stdin)

	fmt.Println("\n\n\t\t\t\t\t======ADD DEGREES======\t\t\t")
	fmt.Print("\n\n\nEnter the student's register number: ")
	degree.RegisterNumber, _ = reader.ReadString('\n')
	degree.RegisterNumber = strings.TrimSpace(degree.RegisterNumber)

	fmt.Print("\n\n\nEnter the subject name: ")
	fmt.Scan(&degree.Subject)

	fmt.Println("\n\n\n\t\t\t\t1- Week 7 (Max Degree: 30)")
	fmt.Println("\t\t\t\t2- Week 12 (Max Degree: 20)")
	fmt.Println("\t\t\t\t3- Coursework (Max Degree: 10)")
	fmt.Println("\t\t\t\t4- Final (Max Degree: 40)")
	fmt.Println("\t\t\t\t__________________________________________")

	var componentChoice int
	fmt.Scan(&componentChoice)

	switch componentChoice {
	case 1:
		for {
			fmt.Print("\t\t\nWeek 7: ")
			fmt.Scan(&degree.Week7)
			if degree.Week7 >= 0 && degree.Week7 <= 30 {
				break
			}
			fmt.Println("Invalid degree. Please enter a value between 0 and 30.")
		}
	case 2:
		for {
			fmt.Print("Week 12: ")
			fmt.Scan(&degree.Week12)
			if degree.Week12 >= 0 && degree.Week12 <= 20 {
				break
			}
			fmt.Println("Invalid degree. Please enter a value between 0 and 20.")
		}
	case 3:
		for {
			fmt.Print("Coursework: ")
			fmt.Scan(&degree.Coursework)
			if degree.Coursework >= 0 && degree.Coursework <= 10 {
				break
			}
			fmt.Println("Invalid degree. Please enter a value between 0 and 10.")
		}
	case 4:
		for {
			fmt.Print("Final: ")
			fmt.Scan(&degree.Final)
			if degree.Final >= 0 && degree.Final <= 40 {
				break
			}
			fmt.Println("Invalid degree. Please enter a value between 0 and 40.")
		}
	default:
		fmt.Println("Invalid component choice.")
		return
	}

	saveDegree(degree)
	fmt.Println("Degrees added successfully.")
	pause()
}

func editDegrees() {
	var subject string
	fmt.Print("\t\t\t\n\n\nEnter the subject name: ")
	fmt.Scan(&subject)

	fmt.Println("Edit functionality not fully implemented in this version.")
	pause()
}

func saveDegree(degree Degree) {
	file, err := os.OpenFile(DegreesFile, os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
	if err != nil {
		fmt.Println("Error opening the file.")
		return
	}
	defer file.Close()

	fmt.Fprintf(file, "Register Number: %s\n", degree.RegisterNumber)
	fmt.Fprintf(file, "Subject Name: %s\n", degree.Subject)
	fmt.Fprintf(file, "Week 7: %d\n", degree.Week7)
	fmt.Fprintf(file, "Week 12: %d\n", degree.Week12)
	fmt.Fprintf(file, "Coursework: %d\n", degree.Coursework)
	fmt.Fprintf(file, "Final: %d\n\n", degree.Final)
}

func loadStudents() ([]Student, error) {
	file, err := os.Open(DBFile)
	if err != nil {
		return []Student{}, err
	}
	defer file.Close()

	var students []Student
	decoder := gob.NewDecoder(file)
	err = decoder.Decode(&students)
	if err != nil {
		return []Student{}, nil // Return empty if file doesn't exist yet
	}

	return students, nil
}

func saveStudents(students []Student) error {
	file, err := os.Create(DBFile)
	if err != nil {
		return err
	}
	defer file.Close()

	encoder := gob.NewEncoder(file)
	return encoder.Encode(students)
}

// Display functions for course tables
func displayCourseTableMath1() {
	subjects := []string{
		"Calculus II", "ESP II", "Communication", "Advanced Physics",
		"Problem Solving", "Entrepreneurship", "Discrete Structure",
	}
	maxMarks := []int{30, 20, 10, 30, 10, 20, 10}

	displayCourseTable(subjects, maxMarks, false)
}

func displayCourseTableMath2() {
	subjects := []string{
		"Calculus I", "ESP I", "Computing", "Physics",
		"Business", "Creativity", "INF System",
	}
	maxMarks := []int{30, 20, 10, 30, 10, 20, 0}

	displayCourseTable(subjects, maxMarks, true)
}

func displayCourseTableScience1() {
	subjects := []string{
		"Pre Calculus", "ESP I", "Computing", "Physics",
		"Business", "Creativity", "INF System",
	}
	maxMarks := []int{30, 20, 10, 30, 10, 20, 10}

	displayCourseTable(subjects, maxMarks, false)
}

func displayCourseTableScience2() {
	subjects := []string{
		"Calculus I", "ESP II", "Communication", "Advanced Physics",
		"Problem Solving", "Entrepreneurship", "Discrete Structure",
	}
	maxMarks := []int{30, 20, 10, 30, 10, 20, 10}

	displayCourseTable(subjects, maxMarks, false)
}

func displayCourseTable(subjects []string, maxMarks []int, showGrades bool) {
	fmt.Println("+--------------------------------------------------------------------------+")
	fmt.Println("|      Subject      |   Week 7   |   Week 12  | Coursework |     Grade    |")
	fmt.Println("+--------------------------------------------------------------------------+")

	grades := []string{"A", "A-", "B+", "B", "C+", "C", "D", "A"}

	for i, subject := range subjects {
		week7 := rando.Intn(maxMarks[i] + 1)
		week12 := rando.Intn(maxMarks[i] + 1)
		coursework := rando.Intn(maxMarks[i] + 1)

		gradeStr := "-"
		if showGrades {
			gradeStr = grades[rando.Intn(len(grades))]
		}

		fmt.Printf("| %-18s| %-10d | %-10d | %-10d | %-12s |\n",
			subject, week7, week12, coursework, gradeStr)
	}

	fmt.Println("+--------------------------------------------------------------------------+")
}

func displayAttendanceMath() {
	subjects := []string{
		"Calculus II", "ESP II", "Communication", "Advanced Physics",
		"Problem Solving", "Entrepreneurship", "Discrete Structure",
	}
	attendance := []float64{0.0, 3.3, 6.0, 12.0, 0.0, 15.0, 9.0}

	displayAttendanceTable(subjects, attendance)
}

func displayAttendanceScience() {
	subjects := []string{"Pre Calculus", "ESP I", "Information System", "Physics", "Computing"}
	attendance := []float64{3.3, 3.3, 15.0, 15.0, 0.0}

	displayAttendanceTable(subjects, attendance)
}

func displayAttendanceTable(subjects []string, attendance []float64) {
	fmt.Println("+---------------------------------+")
	fmt.Println("|      Subject      |  Attendance |")
	fmt.Println("+---------------------------------+")

	for i, subject := range subjects {
		fmt.Printf("| %-18s|   %-6.1f    |\n", subject, attendance[i])
	}

	fmt.Println("+---------------------------------+")
}

func displayTimetableMath() {
	daysOfWeek := []string{"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday"}
	subjects := []string{
		"Advanced Physics", "Discrete Structures", "Entrepreneurship Skills",
		"Calculus II", "Academic Writing", "Academic Writing", "Communication Skills",
	}
	codes := []string{"EBA1106", "CCS1001", "CNC1401", "EBA1204", "UNR1407", "UNR1407", "UNR2101"}
	times := [][2]string{
		{"8:30 AM", "10:30 AM"},
		{"10:30 AM", "12:30 PM"},
		{"6:30 PM", "8:30 PM"},
		{"10:30 AM", "12:30 PM"},
		{"12:30 PM", "2:30 PM"},
		{"2:30 PM", "4:30 PM"},
		{"8:30 AM", "10:30 AM"},
	}

	displayTimetableTable(daysOfWeek, subjects, codes, times)
}

func displayTimetableScience1() {
	daysOfWeek := []string{"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday"}
	subjects := []string{
		"Pre Calculus", "ESP I", "Communication",
		"Problem Solving", "Advanced Physics", "Problem Solving",
	}
	codes := []string{"EBA1106", "CCS1001", "CNC1401", "UNR1407", "EBA1204", "UNR2101"}
	times := [][2]string{
		{"8:30 AM", "10:30 AM"},
		{"6:30 PM", "8:30 PM"},
		{"12:30 PM", "2:30 PM"},
		{"2:30 PM", "4:30 PM"},
		{"8:30 AM", "10:30 AM"},
		{"4:30 PM", "6:30 PM"},
	}

	displayTimetableTable(daysOfWeek, subjects, codes, times)
}

func displayTimetableScience2() {
	daysOfWeek := []string{"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday"}
	subjects := []string{
		"Advanced Physics", "Discrete Structures", "Entrepreneurship Skills",
		"Calculus I", "Academic Writing", "Academic Writing", "Communication Skills",
	}
	codes := []string{"EBA1106", "CCS1001", "CNC1401", "EBA1204", "UNR1407", "UNR1407", "UNR2101"}
	times := [][2]string{
		{"8:30 AM", "10:30 AM"},
		{"10:30 AM", "12:30 PM"},
		{"6:30 PM", "8:30 PM"},
		{"10:30 AM", "12:30 PM"},
		{"12:30 PM", "2:30 PM"},
		{"2:30 PM", "4:30 PM"},
		{"8:30 AM", "10:30 AM"},
	}

	displayTimetableTable(daysOfWeek, subjects, codes, times)
}

func displayTimetableTable(days []string, subjects []string, codes []string, times [][2]string) {
	fmt.Println("+---------------------------------------------------------------------------------+")
	fmt.Println("|       Day       |  Course Start  |   Course End   |     Code     |    Subject     |")
	fmt.Println("+---------------------------------------------------------------------------------+")

	for i := 0; i < len(subjects); i++ {
		dayIndex := i % len(days)
		fmt.Printf("| %-16s| %-14s | %-14s | %-12s | %-14s |\n",
			days[dayIndex], times[i][0], times[i][1], codes[i], subjects[i])
	}

	fmt.Println("+---------------------------------------------------------------------------------+")
}

// Utility functions
func clearScreen() {
	fmt.Print("\033[H\033[2J")
}

func pause() {
	reader := bufio.NewReader(os.Stdin)
	reader.ReadString('\n')
}
