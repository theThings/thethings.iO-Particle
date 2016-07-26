
/*
   params: is an object with the keys:
    - action: one of 'write' | 'read'
    - thingToken: the thing that triggered the trigger
    - values: only if action == 'write'. Is an array of values where each value is an object with:
    - key: the key
    - value: the data sent
    - datetime: (can be null)

   callback: is a function to be called when the trigger ends can contain a
       parameter string *error* if the trigger needs to report an error.
*/

function trigger(params, callback){
  if (params.action !== 'write') return callback();
  var values = {
      values: params.values
    };
  
  var fortune_cookies = ["Today it's up to you to create the peacefulness you long for.",
"A friend asks only for your time not your money.",
"If you refuse to accept anything but the best, you very often get it.",
"A smile is your passport into the hearts of others.",
"A good way to keep healthy is to eat more Chinese food.",
"Your high-minded principles spell success.",
"Hard work pays off in the future, laziness pays off now.",
"Change can hurt, but it leads a path to something better.",
"Enjoy the good luck a companion brings you.",
"People are naturally attracted to you.",
"Hidden in a valley beside an open stream- This will be the type of place where you will find your dream.",
"A chance meeting opens new doors to success and friendship.",
"You learn from your mistakes... You will learn a lot today.",
"If you have something good in your life, don't let it go!",
"What ever you're goal is in life, embrace it visualize it, and for it will be yours.",
"Your shoes will make you happy today.",
"You cannot love life until you live the life you love.",
"Be on the lookout for coming events; They cast their shadows beforehand.",
"Land is always on the mind of a flying bird.",
"The man or woman you desire feels the same about you.",
"Meeting adversity well is the source of your strength.",
"A dream you have will come true.",
"Our deeds determine us, as much as we determine our deeds.",
"Never give up. You're not a failure if you don't give up.",
"You will become great if you believe in yourself.",
"There is no greater pleasure than seeing your loved ones prosper.",
"You will marry your lover.",
"A very attractive person has a message for you.",
"You already know the answer to the questions lingering inside your head.",
"It is now, and in this world, that we must live.",
"You must try, or hate yourself for not trying.",
"You can make your own happiness.",
"The greatest risk is not taking one.",
"The love of your life is stepping into your planet this summer.",
"Love can last a lifetime, if you want it to.",
"Adversity is the parent of virtue.",
"Serious trouble will bypass you.",
"A short stranger will soon enter your life with blessings to share.",
"Now is the time to try something new.",
"Wealth awaits you very soon.",
"If you feel you are right, stand firmly by your convictions.",
"If winter comes, can spring be far behind?",
"Keep your eye out for someone special.",
"You are very talented in many ways.",
"A stranger, is a friend you have not spoken to yet.",
"A new voyage will fill your life with untold memories.",
"You will travel to many exotic places in your lifetime.",
"Your ability for accomplishment will follow with success.",
"Nothing astonishes men so much as common sense and plain dealing.",
"Its amazing how much good you can do if you dont care who gets the credit."];
  
  for (var i = 0; i < values.values.length; ++i) {
    if (values.values[i].key == 'buttonPressed' && values.values[i].value == '1') {
    	var inputTwitter = {
          'status': 'Awesome things happening!'
        }
        inputTwitter.status = fortune_cookies[Math.floor((Math.random() * 50))];
        
         var twitter = new Twitter({
            accessToken: '',
            accessTokenSecret: '',
            consumerKey: '',
            consumerSecret: ''
 		 });

  		 twitter.postTweet(inputTwitter, callback);
      
      	console.log(values);
    	values.values[0].key = 'blink';
    	values.values[0].value = '1';
  		thethingsAPI.thingWrite(
    	  'your token',
    	  values,
    	  function() { callback(null, 'ok'); }
    	);
      	values.values[0].key = 'fortuneCookie';
    	values.values[0].value = inputTwitter.status;
  		thethingsAPI.thingWrite(
    	  'your token',
    	  values,
    	  function() { callback(null, 'ok'); }
    	);
      
  	}
  }
  console.log(values);
  
  
   callback();
}

