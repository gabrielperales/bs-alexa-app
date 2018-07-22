open AlexaApp;

let expressApp = Express.express();
let alexaApp = app("AlexaApp");

alexaApp |> express(config(~expressApp, ()));

alexaApp
|> launch((_, res) =>
     res
     |> Response.say("Welcome to the Alexa Skills Kit, you can say hello!")
   );

alexaApp
|> intent(~name="HelloWorldIntent", (_, res) =>
     res |> Response.say("Hello world!")
   );

let port = 8080;

let onListen = e =>
  switch (e) {
  | exception (Js.Exn.Error(e)) =>
    Js.log(e);
    Node.Process.exit(1);
  | _ => Js.log @@ "Listening at http://127.0.0.1:" ++ string_of_int(port)
  };

Express.App.listen(expressApp, ~port, ~onListen, ());
