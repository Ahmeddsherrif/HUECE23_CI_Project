import sys
from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QVBoxLayout, QHBoxLayout, QPushButton
from PyQt5.QtCore import Qt, QTimer
import serial

class Application(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Serial Control")
        self.serial = serial.Serial('/dev/ttyACM0', 9600)  # Replace 'COM1' with your serial port

        # Create labels and numbers
        self.labels = ['A', 'B', 'C', 'D']
        self.number_labels = []
        self.number_vars = []

        layout = QVBoxLayout()

        # Create and add the "Hello" label
        hello_label = QLabel("IDLE")
        hello_label.setAlignment(Qt.AlignCenter)
        layout.addWidget(hello_label)
        
        for label in self.labels:
            label_text = f"{label}:"
            number_var = 0
            self.number_vars.append(number_var)

            label_widget = QLabel(label_text)
            number_label = QLabel(str(number_var))
            self.number_labels.append(number_label)

            hbox = QHBoxLayout()
            hbox.addWidget(label_widget)
            hbox.addWidget(number_label)
            layout.addLayout(hbox)

        # Create buttons
        button_layout = QHBoxLayout()
        
        button_start = QPushButton("Start", clicked=self.start_serial)
        button_stop = QPushButton("Stop", clicked=self.stop_serial)
        button_reset = QPushButton("Reset", clicked=self.reset_numbers)
        
        button_layout.addWidget(button_start)
        button_layout.addWidget(button_stop)
        button_layout.addWidget(button_reset)
        
        layout.addLayout(button_layout)
        self.setLayout(layout)

        # Create a QTimer to periodically read from the serial port
        self.timer = QTimer()
        self.timer.timeout.connect(self.check_serial)
        self.timer.start(100)  # Read every 100 milliseconds

    def start_serial(self):
        self.serial.write(b'S')
        

    def stop_serial(self):
        self.serial.write(b'x')

    def reset_numbers(self):
        for i in range(len(self.number_vars)):
            self.number_vars[i] = 0
            self.number_labels[i].setText(str(self.number_vars[i]))

    def check_serial(self):
        if self.serial.in_waiting:
            data = self.serial.read_until(b'\n').decode('utf-8')
            i = ord(data[4])-48-1
            print(i)
            self.number_vars[i] += 1
            self.number_labels[i].setText(str(self.number_vars[i]))


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = Application()
    window.show()
    sys.exit(app.exec_())
