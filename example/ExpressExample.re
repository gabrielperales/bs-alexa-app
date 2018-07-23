open AlexaApp;

let expressApp = Express.express();
let alexaApp = app("AlexaApp");

alexaApp
|> express(
     config(
       ~expressApp,
       /* verifies requests come from amazon alexa. Must be enabled for production.
          You can disable this if you're running a dev environment and want to POST
          things to test behavior. enabled by default.
          */
       ~checkCert=false,
       /* sets up a GET route when set to true. This is handy for testing in
          development, but not recommended for production. disabled by default
          */
       ~debug=true,
       (),
     ),
   );

alexaApp
|> launch((_, res) =>
     res
     |> Response.say("Welcome to the Alexa Skills Kit, you can say hello!")
   );

alexaApp
|> intent(~name="HelloWorldIntent", (_, res) =>
     res |> Response.say("Hello world!")
   );

let port =
  Node.Process.process##env
  |> Js.Dict.get(_, "PORT")
  |> Belt.Option.mapWithDefault(_, 8080, int_of_string);

let onListen = e =>
  switch (e) {
  | exception (Js.Exn.Error(e)) =>
    Js.log(e);
    Node.Process.exit(1);
  | _ => Js.log @@ "Listening at http://127.0.0.1:" ++ string_of_int(port)
  };

Express.App.listen(expressApp, ~port, ~onListen, ());
