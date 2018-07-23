open AlexaApp;

let alexaApp = app();

alexaApp |> launch((_, res) => res |> Response.say("Hello world"));

let handler = alexaApp |> lambda;
