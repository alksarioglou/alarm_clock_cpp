//Alkinoos Sarioglou
//ID:10136315
//Group 4
//The code implements all functionality features of the clock

#include "mbed.h"
#include "C12832.h"

class Date  {
protected:
    int day,month,year;
    int leap;
public:
    Date(int d,int mo,int y) : day(d),month(mo),year(y) {leap=0;}
            
    void incrementday(void) {
        day++;
    }

    void resetday (void) {
        day=1;
        month++;
    }
    
    void resetmonth (void) {
        month=1;
        year++;
    }
    
    void resetyear(void) {
        year=2000;
    }
    
    int returnday (void) {
        return day;
    }
    
    int returnmonth (void) {
        return month;
    }
    
    int returnyear(void) {
        return year;
    }
    
    int checkleap(void) {
        if (year % 4 == 0) {
            if (year % 100 == 0) {
                if (year % 400 == 0)
                    leap=1;
            else
                    leap=0;
            }
            else
                    leap=1;
        }
        else
                    leap=0;
        return leap;
    }
};

class Time  {
protected:
    Ticker ttt;
    Timeout t;
    int sec,min,hour;
public:
    Time(int h,int m,int s) : hour(h),min(m),sec(s) {ttt.attach(callback(this, &Time::increment),1);}
    
    void increment(void) {
        sec++;
        if (sec==60) {
            resetsec();
        }
        else if (min==59 && sec==59 && hour!=23) {
            t.attach(callback(this,&Time::resetmin),1);
        }
        else if (hour==23 and min==59 and sec==59) {
            t.attach(callback(this,&Time::resethour),1);
        }
    }
    
    void resetsec(void) {
        sec=0;
        min++;
    }
    
    void resetmin(void) {
        min=0;
        hour++;
    }
    void resethour(void) {
        hour=0;
        sec=0;
        min=0;
    }
    int returnsec(void) {
        return sec;
    }
    
    int returnmin(void) {
        return min;
    }
    
    int returnhour(void) {
        return hour;
    }
    
};

class Alarm  {
protected:
    int alarmhour,alarmmin;
public:
    Alarm (int alh,int alm) : alarmhour(alh),alarmmin(alm) {}

    int returnalarmhour (void) {
        return alarmhour;
    }
    
    int returnalarmmin (void) {
        return alarmmin;
    }
      

};

float note1[18]= {783.99,783.99,1174.7,1174.7,1318.5,1318.5,1174.7,1046.5,1046.5,
                 987.76,987.76,880.0,880.0,783.99,0.0};
float duration1[18]= {0.48,0.48,0.48,0.48,0.48,0.48,0.8,0.48,0.48,
                     0.48,0.48,0.48,0.48,0.72,0.0}; 
float note2[30]= {987.76,987.76,987.76,987.76,987.76,987.76,987.76,1174.7,783.99,880.0,987.76,
                1046.5,1046.5,1046.5,1046.5,1046.5,987.76,987.76,987.76,1174.7,1174.7,987.76,880.0,783.99,0.0};
float duration2[30]= {0.48,0.48,1,0.48,0.48,1,0.48,0.48,0.48,
                     0.48,2,0.48,0.48,0.48,0.48,0.48,0.48,0.48,0.48,0.48,0.48,0.48,0.48,0.72,0.0};  

class speaker {
public:
    speaker (PinName pin) : _pin(pin) {}
    void PlaySong(float frequency[], float duration[], float volume=1.0) {
        vol = volume;
        notecount = 0;
        _pin.period(1.0/frequency[notecount]);
        _pin = volume/2.0;
        noteduration.attach(this,&speaker::nextnote, duration[notecount]);
        frequencyptr = frequency;
        durationptr = duration;
    }
    void nextnote(void) {
        _pin = 0.0;
    notecount++; 
    if (durationptr[notecount]!=0.0) {
        _pin.period(1.0/frequencyptr[notecount]);
        noteduration.attach(this,&speaker::nextnote, durationptr[notecount]);
        _pin = vol/2.0;
    } else
        _pin = 0.0;
    }
private:
    Timeout noteduration;
    PwmOut _pin;
    int notecount;
    float vol;
    float * frequencyptr;
    float * durationptr;
};

class LED {
private:
    DigitalOut outputSignal;
public:
    LED(PinName pin) : outputSignal(pin) {}
    void on(void) {outputSignal = 0;}
    void off(void) {outputSignal = 1;}
    void toggle(void) {
        if (outputSignal.read()) 
            outputSignal = 0;
        else 
            outputSignal = 1;
    }
    int status(void) {return outputSignal.read();}
};

class joystick  {
protected:
    InterruptIn up,down,right,left,centre;
public:
    joystick(PinName pin1,PinName pin12,PinName pin2,PinName pin3,PinName pin4): up(pin1),centre(pin12),down(pin2),right(pin3),left(pin4) {
        
        //up.rise(callback(this,&joystick::sequence));
        //up.fall(callback(this,&joystick::off));
        //down.rise(callback(this,&joystick::sequence));
        //down.fall(callback(this,&joystick::off));  
        //left.rise(callback(this,&joystick::sequence));
        //left.fall(callback(this,&joystick::off));
        //right.rise(callback(this,&joystick::sequence));
        //right.fall(callback(this,&joystick::off));
        //centre.rise(callback(this,&joystick::sequence));     
        //centre.fall(callback(this,&joystick::off));
        
        }
        
        int checkforcentre(void) {
            if (centre.read()==1) {
                return 1;
            }
            else return 0;
        }
        
        int checkforup(void) {
            if (up.read()==1) {
                return 1;
            }
            else return 0;
        }
        
        int checkfordown(void) {
            if (down.read()==1) {
                return 1;
            }
            else return 0;
        }
        
        int checkforright(void) {
            if (right.read()==1) {
                return 1;
            }
            else return 0;
        }
        
        int checkforleft(void) {
            if (left.read()==1) {
                return 1;
            }
            else return 0;
        }
        
        
};

class Display : public Time,public joystick,public Date,public Alarm,public speaker {
protected:
    C12832* lcd;
    enum state {none,timeset,dateset,alarmset,worldclock,alarmring1,alarmring2};
    state st;
    enum alarmcond {active1,active2,inactive};
    alarmcond con;
    double period;
    int nyhour,shanghour;
    int leap;
    int alarmday;
    LED green,red,blue;
public:
    Display (int h,int m,int s,PinName pin1,PinName pin12,PinName pin2,PinName pin3,PinName pin4,int d,int mo,int y,int alh,int alm,PinName pin,PinName pin5,PinName pin6,PinName pin7,C12832* dsp) : Time(h,m,s),joystick(pin1,pin12,pin2,pin3,pin4),Date(d,mo,y),Alarm(alh,alm),speaker(pin),green(pin5),red(pin6),blue(pin7),lcd(dsp) {alarmday=day,st=none,con=inactive,leap=0;}
    
    void changestate(void) {
        if (st==none) {
            red.off();
            blue.off();
            green.off();
            display();
        }
        else if (st==timeset) {
            settime();
        }
        else if (st==dateset) {
            setdate();
        }
        else if (st==alarmset) {
            red.off();
            blue.off();
            green.off();
            setalarm();
        }
        else if (st==worldclock) {
            red.off();
            blue.off();
            green.off();
            showworld();
        }
        else if (st==alarmring1) {
            red.on();
            blue.on();
            alarmactive1();
        }
        else if (st==alarmring2) {
            green.on();
            blue.on();
            alarmactive2();
        }
    }
    
    void display(void) {
        
        lcd->locate(0,3);
        lcd->printf("Time:");
        lcd->locate(0,15);
        lcd->printf("%d : %d : %d",returnhour(),returnmin(),returnsec());
        lcd->locate(60,3);
        lcd->printf("Date:");
        lcd->locate(60,15);
        lcd->printf("%d / %d / %d",returnday(),returnmonth(),returnyear());
        if (checkforcentre()==1) {
            lcd->cls();
            st=timeset;
        }
        else if (checkforright()==1) {
            lcd->cls();
            st=dateset;
        }
        else if (checkforleft()==1) {
            lcd->cls();
            alarmday=day;
            st=alarmset;
        }
        else if (checkfordown()==1) {
            lcd->cls();
            st=worldclock;
        }
        else if (hour==alarmhour && min==alarmmin && sec==1 && day==alarmday && con==active1) {
            st=alarmring1;
        }
        else if (hour==alarmhour && min==alarmmin && sec==1 && day==alarmday && con==active2) {
            st=alarmring2;   
        }
        else if (min==0 and sec==0 and hour!=0) {
            st=alarmring1;   
        }
        else if ((min==10 && sec==0) || (min==20 && sec==0) || (min==30 && sec==0) || (min==40 && sec==0) || (min==50 && sec==0)) {
            st=alarmring1;
        }
        else st=none;
        
    }
    
    void settime(void) {
        lcd->locate(0,3);
        lcd->printf("Set Time:");
        lcd->locate(0,15);
        lcd->printf("%d : %d : %d",returnhour(),returnmin(),returnsec());
        if (checkforup()==1) {
            hour++;
            if (hour==24) {
                lcd->cls();
                hour=0;
            }
        }
        else if(checkforright()==1) {
            min++;
            if (min==60) {
                lcd->cls();
                min=0;
            }
        }
        else if(checkforleft()==1) {
            sec++;
            if (sec==60) {
                lcd->cls();
                sec=0;
            }
        }
        else if(checkfordown()==1) {
           lcd->cls();
           st=none;
        }
    }
       
    void setdate(void) {
        lcd->locate(60,3);
        lcd->printf("Set Date:");
        lcd->locate(60,15);
        lcd->printf("%d / %d / %d",returnday(),returnmonth(),returnyear());
        if (checkforup()==1) {
            day++;
            if (month==1||month==3||month==5||month==7||month==8||month==10||month==12) {
                if (day==32) {
                    day=1;
                }
            }
            else if (month==4||month==6||month==9||month==11) {
                if (day==31) {
                    day=1;
                }
            }
            else {
                if (year%4==0) {
                    if (year%100==0) {
                        if (year%400==0) {
                            if(day==30) {
                                day=1;   
                            }
                            leap=1;
                        }
                        else {
                            if(day==29) {
                                day=1;
                            }
                            leap=0;
                        }
                    }
                    else {
                                   if(day==30) {
                                       day=1;
                                    }
                                    leap=1;
                    }
                } 
                else {
                        if (day==29) {
                            day=1;
                        }
                        leap=0;
                }
            }
        }
        else if(checkforright()==1) {
            month++;
            if (month==13) {
                lcd->cls();
                month=1;
            }
        }
        else if(checkforleft()==1) {
            year++;
            if (year==2101) {
                lcd->cls();
                year=2000;
            }
            else if(checkleap()==1) {
                lcd->locate(0,14);
                lcd->printf("Leap Year");
            }
            else if(checkleap()==0) {
                lcd->cls();
            }
        }
        else if(checkfordown()==1) {
           lcd->cls();
           st=none;
        }
    
    }
    
    void setalarm(void) {
        lcd->locate(0,3);
        lcd->printf("Set Alarm:");
        lcd->locate(0,15);
        lcd->printf("%d : %d",returnalarmhour(),returnalarmmin());
        lcd->locate(64,3);
        lcd->printf("Day:");
        lcd->locate(64,15);
        lcd->printf("%d / %d",alarmday,returnmonth());
        
        if (checkforup()==1) {
            alarmhour++;
            if (alarmhour==24) {
                lcd->cls();
                alarmhour=0;
            }
        }
        else if(checkforright()==1) {
            alarmmin++;
            if (alarmmin==60) {
                lcd->cls();
                alarmmin=0;
            }
        }
        else if(checkforleft()==1) {
            alarmday++;
            if (alarmday==32) {
                lcd->cls();
                alarmday=1;
            }
        }
        else if(checkfordown()==1) {
           lcd->cls();
           con=active1;
           st=none;
        }
        else if(checkforcentre()==1) {
            lcd->cls();
            con=active2;
            st=none;
        }
           
    
    }
    
    int returnnyhour(void) {
        nyhour=returnhour()-5;
        if (nyhour==-1) {
            nyhour=23;
        }
        else if (nyhour==-2) {
            nyhour=22;
        }
        else if (nyhour==-3) {
            nyhour=21;
        }
        else if (nyhour==-4) {
            nyhour=20;
        }
        else if (nyhour==-5) {
            nyhour=19;
        }
        
        return nyhour;
    }
    
    int returnshanghour(void) {
        shanghour = returnhour()+8;
        
        if (shanghour==24) {
            shanghour=0;
        }
        else if (shanghour==25) {
            shanghour=1;
        }
        else if (shanghour==26) {
            shanghour=2;
        }
        else if (shanghour==27) {
            shanghour=3;
        }
        else if (shanghour==28) {
            shanghour=4;
        }
        else if (shanghour==29) {
            shanghour=5;
        }
        else if (shanghour==30) {
            shanghour=6;
        }
        else if (shanghour==31) {
            shanghour=7;
        }
        
        return shanghour;
        
    }
    
    void showworld(void) {
        lcd->locate(0,3);
        lcd->printf("New York");
        lcd->locate(0,15);
        lcd->printf("%d : %d",returnnyhour(),returnmin());
        lcd->locate(64,3);
        lcd->printf("Shanghai");
        lcd->locate(64,15);
        lcd->printf("%d : %d",returnshanghour(),returnmin());
        
        if (checkforcentre()==1) {
            lcd->cls();
            st=none;
        }
        
    }
    
    void alarmactive1 (void) {  
        lcd->cls();
        PlaySong(note1,duration1);
        while (st==alarmring1) {
            lcd->locate(0,3);
            lcd->printf("Time:");
            lcd->locate(0,15);
            lcd->printf("%d : %d : %d",returnhour(),returnmin(),returnsec());
            lcd->locate(60,3);
            lcd->printf("Date:");
            lcd->locate(60,15);
            lcd->printf("%d / %d / %d",returnday(),returnmonth(),returnyear());
            if (checkforcentre()==1) {
            lcd->cls();
            st=none;
            }
            if (checkfordown()==1) {
            lcd->cls();
            st=none;
            alarmmin=alarmmin+1;
            }    
        }
        
    }
    
    void alarmactive2 (void) { 
        lcd->cls(); 
        PlaySong(note2,duration2);
        while (st==alarmring2) {
            lcd->locate(0,3);
            lcd->printf("Time:");
            lcd->locate(0,15);
            lcd->printf("%d : %d : %d",returnhour(),returnmin(),returnsec());
            lcd->locate(60,3);
            lcd->printf("Date:");
            lcd->locate(60,15);
            lcd->printf("%d / %d / %d",returnday(),returnmonth(),returnyear());
            if (checkforcentre()==1) {
            lcd->cls();
            st=none;
            }
            if (checkfordown()==1) {
            lcd->cls();
            st=none;
            alarmmin=alarmmin+1;
            }    
        }
        
    }
    
    
};      
                                  
    
int main(void) {
    C12832* one = new C12832 (D11, D13, D12, D7, D10);
    joystick j(A2,D4,A3,A5,A4);
    Display k(0,0,0,A2,D4,A3,A5,A4,1,1,2018,0,0,D6,D9,D5,D8,one);
    one->cls();
    while(1) {
        k.changestate();  
    }
}