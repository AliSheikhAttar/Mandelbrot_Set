use_synth :pretty_bell#hoover,dark_ambience
#hollow   #pretty_bell #prophet   #sine


with_fx :reverb, slowed: 0.6 do
  live_loop :note_s4 do
    sleep 20
    play choose([:D4,:Cs4]), attack: 12, release: 9, amp: 0.4
    sleep 120
  end
  live_loop :note_s3 do
    sleep 17
    play :G4,  attack: 13, release: 9
    sleep 120
  end
  live_loop :notes_2 do
    sleep 10
    play :Fs4, amp: 0.7 , attack: 16, release: 9
    sleep 120
  end
  
  live_loop :note_s1 do
    sleep 2
    play :c3, attack:8, release: 6 , amp: 0.4
    sleep 120
  end
  
  
end
live_loop :peak do
  sleep 22
  with_fx :reverb, kill_delay: 0.2, room: 0.9 do
    4.times do
      use_random_seed 4000
      12.times do
        sleep 0.25
        play chord(:e3, :m7).choose, release: 0.1, pan: rrand(-1, 1, res: 0.9), amp: 0.6
      end
    end
    with_fx :reverb, kill_delay: 0.2, room: 0.3 do
      4.times do
        use_random_seed 4000
        12.times do
          sleep 0.25
          play chord(:e4, :m11).choose, release: 0.1, pan: rrand(-1, 1, res: 0.9), amp: 0.7
        end
      end
    end
    with_fx :reverb, kill_delay: 0.2, room: 0.3 do
      4.times do
        use_random_seed 4000
        12.times do
          sleep 0.25
          play chord(:e5, :m11).choose, release: 0.1, pan: rrand(-1, 1, res: 0.9), amp: 0.7
        end
      end
      12.times do
        sleep 0.25
        play chord(:e4, :m7).choose, release: 5, pan: rrand(-1, 1, res: 0.9), amp: 0.6
      end
    end
  end
  sleep 120
end
use_synth :dark_ambience#hoover,dark_ambienceprophet
live_loop :note1f do
  sleep 58
  play choose([:e4, :G4]), attack:15, release: 8
  sleep 19
end
live_loop :note2f do
  sleep 59
  play choose([:A5]), attack:12, release: 5
  sleep 19
end

live_loop :note3f do
  sleep 61
  play choose([:D4, :E4]), attack:12, release: 5
  sleep 19
end
use_synth :hollow#hoover,dark_ambienceprophet
live_loop :note4f do
  sleep 65
  play choose([:D4,:E4]), attack: 11, release: 10 , amp: 0.8
  sleep 19
end

live_loop :note5f do
  sleep 70
  play choose([:Fs4,:G4]), attack: 11, release: 10 , amp: 0.8
  sleep 19
end
live_loop :note6f do
  sleep 76
  play :e6, attack: 12, release: 10 , amp: 1.4
  sleep 19
end

live_loop :note7f do
  sleep 70
  play choose([:A4, :Cs5]), attack: 11, release: 10 , amp: 0.8
  sleep 19
end
