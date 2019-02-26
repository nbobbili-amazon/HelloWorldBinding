
static const char _afb_description_helloworld[] =
    "{\"openapi\":\"3.0.0\",\"$schema\":\"http://iot.bzh/download/openapi/sch"
    "ema-3.0/default-schema.json\",\"info\":{\"description\":\"\",\"title\":\""
    "Hello World Binding Example\",\"version\":\"0.1\",\"x-binding-c-generato"
    "r\":{\"api\":\"helloworld\",\"version\":3,\"prefix\":\"afv_\",\"postfix\""
    ":\"\",\"start\":null,\"onevent\":null,\"init\":\"init\",\"scope\":\"\",\""
    "private\":false,\"noconcurrency\":true}},\"servers\":[{\"url\":\"ws://{h"
    "ost}:{port}/api/monitor\",\"description\":\"TS caching binding\",\"varia"
    "bles\":{\"host\":{\"default\":\"localhost\"},\"port\":{\"default\":\"123"
    "4\"}},\"x-afb-events\":[{\"$ref\":\"#/components/schemas/afb-event\"}]}]"
    ",\"components\":{\"schemas\":{\"afb-reply\":{\"$ref\":\"#/components/sch"
    "emas/afb-reply-v3\"},\"afb-event\":{\"$ref\":\"#/components/schemas/afb-"
    "event-v3\"},\"afb-reply-v3\":{\"title\":\"Generic response.\",\"type\":\""
    "object\",\"required\":[\"jtype\",\"request\"],\"properties\":{\"jtype\":"
    "{\"type\":\"string\",\"const\":\"afb-reply\"},\"request\":{\"type\":\"ob"
    "ject\",\"required\":[\"status\"],\"properties\":{\"status\":{\"type\":\""
    "string\"},\"info\":{\"type\":\"string\"},\"token\":{\"type\":\"string\"}"
    ",\"uuid\":{\"type\":\"string\"},\"reqid\":{\"type\":\"string\"}}},\"resp"
    "onse\":{\"type\":\"object\"}}},\"afb-event-v3\":{\"type\":\"object\",\"r"
    "equired\":[\"jtype\",\"event\"],\"properties\":{\"jtype\":{\"type\":\"st"
    "ring\",\"const\":\"afb-event\"},\"event\":{\"type\":\"string\"},\"data\""
    ":{\"type\":\"object\"}}}},\"responses\":{\"200\":{\"description\":\"A co"
    "mplex object array response\",\"content\":{\"application/json\":{\"schem"
    "a\":{\"$ref\":\"#/components/schemas/afb-reply\"}}}}}}}"
;


static const struct afb_verb_v3 _afb_verbs_helloworld[] = {
    {
        .verb = NULL,
        .callback = NULL,
        .auth = NULL,
        .info = NULL,
        .session = 0,
        .vcbdata = NULL,
        .glob = 0
	}
};

const struct afb_binding_v3 afbBindingV3 = {
    .api = "helloworld",
    .specification = _afb_description_helloworld,
    .info = "",
    .verbs = _afb_verbs_helloworld,
    .preinit = NULL,
    .init = init,
    .onevent = NULL,
    .userdata = NULL,
    .noconcurrency = 1
};

