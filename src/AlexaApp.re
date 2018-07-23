type alexaApp;
type complete;

module Response = {
  type t;
  [@bs.send.pipe: t] external say : string => alexaApp = "say";
  [@bs.send.pipe: t] external clear : unit => alexaApp = "clear";
  [@bs.send.pipe: t] external reprompt : string => alexaApp = "reprompt";
  [@bs.send.pipe: t]
  external card : (string, ~content: string=?, unit) => alexaApp = "card";
  [@bs.send.pipe: t] external linkAccount : unit => alexaApp = "linkAccount";
  [@bs.send.pipe: t] external send : unit => Js.Promise.t(complete) = "send";
  [@bs.send.pipe: t]
  external fail : string => Js.Promise.t(complete) = "send";
};

module Request = {
  type t = {.};
};

[@bs.module "alexa-app"] [@bs.new]
external app : (~name: string=?, unit) => alexaApp = "";

[@bs.deriving abstract]
type config = {
  expressApp: Express.App.t,
  [@bs.optional]
  checkCert: bool,
  [@bs.optional]
  debug: bool,
};

[@bs.send.pipe: alexaApp] external express : config => alexaApp = "express";

[@bs.send.pipe: alexaApp]
external launch : ((Request.t, Response.t) => alexaApp) => alexaApp = "launch";

[@bs.send.pipe: alexaApp] external lambda : 'lambdaHandler = "lambda";

type slot = {
  name: string,
  slotType: string,
};

[@bs.send.pipe: alexaApp]
external intent :
  (~name: string, (Request.t, Response.t) => alexaApp) => alexaApp =
  "intent";
