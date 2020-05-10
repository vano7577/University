`use strict`

const {Sequelize, DataTypes, Model} = require('sequelize');

const sequelize = new Sequelize('poll_orm', 'root', '0501', {
    host: 'localhost',
    dialect: 'mysql',
    define: {
        timestamps: false
    }  });

const poll_include_json = require('./poll_include.json');
const prop_ison = require('./prop.json');
const poll_json = require('../JSON/poll.json');
const alternative_json = require('./alternative.json');
const alternative_prop_json = require('./alternative_prop.json');
const user_json = require('./user.json');
const question_json = require('./question.json');
const question_prop_json = require('./question_prop.json');
const session_json = require('./session.json');
const response_json = require('./response.json');
const response_prop_json = require('./response_prop.json');

const User = sequelize.define("user", {
  user_id:{    allowNull: false,
    autoIncrement: true,
    primaryKey: true,
    type: Sequelize.DataTypes.INTEGER  },
    name: DataTypes.STRING,
    photo: DataTypes.STRING,
    email: DataTypes.STRING 

},
{ freezeTableName: true}
  )

const Poll = sequelize.define("poll", {
  poll_id:{     allowNull: false,
    autoIncrement: true,
    primaryKey: true,
    type: Sequelize.DataTypes.INTEGER
  },
  name:DataTypes.STRING
},
{
       freezeTableName: true
}
)

const Prop = sequelize.define("prop", {
    report: DataTypes.STRING
},
{
       freezeTableName: true
}
)

const Include = sequelize.define("include", {

   },
{
       freezeTableName: true
}
)

const Session = sequelize.define("session", {
    session_id:{     allowNull: false,
        autoIncrement: true,
        primaryKey: true,
        type: Sequelize.DataTypes.INTEGER
    },
    start: DataTypes.DATE,
    end: DataTypes.DATE
    },
    {
           freezeTableName: true
    }
)

const Question = sequelize.define("question", {
  question_id:{     allowNull: false,
    autoIncrement: true,
    primaryKey: true,
    type: Sequelize.DataTypes.INTEGER
}},
{
       freezeTableName: true
}
)

const Response = sequelize.define("response", {
  response_id:{    allowNull: false,
    autoIncrement: true,
    primaryKey: true,
    type: Sequelize.DataTypes.INTEGER
}},
{
       freezeTableName: true
}
)
const Response_prop = sequelize.define("response_prop", { 
  reponse_prop_id:{     allowNull: false,
    autoIncrement: true,
    primaryKey: true,
    type: Sequelize.DataTypes.INTEGER
}, 
    action: DataTypes.STRING
  },
{
       freezeTableName: true
}
)

const Alternative = sequelize.define("alternative", {
  alternative_id:{    allowNull: false,
    autoIncrement: true,
    primaryKey: true,
    type: Sequelize.DataTypes.INTEGER
}},
{
       freezeTableName: true
}
)

const Alternative_prop = sequelize.define("alternative_prop", { 
  value: DataTypes.STRING}, 
{
       freezeTableName: true
}
)

const Question_prop = sequelize.define("question_prop", { 
  
    value: DataTypes.STRING},
{
       freezeTableName: true
}
)


//poll-PROP
Poll.hasMany(Prop,{
  foreignKey: "poll_id"

});
Prop.belongsTo(Poll,{
  foreignKey: "poll_id"
}
  );

//poll-INCLUDE
Poll.hasMany(Include,{
  foreignKey:"poll_id_from",
  foreignKey:"poll_id_to"
})

Include.belongsTo(Poll,{

  foreignKey:"poll_id_from"
})
Include.belongsTo(Poll,{
  foreignKey:"poll_id_to"
})
Include.removeAttribute('pollPollId');

//poll-SESSION
Poll.hasMany(Session,{
  foreignKey: "poll_id"
})
Session.belongsTo(Poll,{
  foreignKey:"poll_id"
});

//poll-Question
Poll.hasMany(Question,{
  foreignKey: "poll_id"
})
Question.belongsTo(Poll,{
  foreignKey:"poll_id"
})

//u
User.hasMany(Session,{
  foreignKey: "user_id"
})
Session.belongsTo(User,{
  foreignKey:"user_id"
});

Response.hasMany(Response_prop,{
  foreignKey: "response_id"
})
Response_prop.belongsTo(Response,{
  foreignKey: "response_id"
});

Session.hasMany(Response,{
  foreignKey: "session_id"
})
Response.belongsTo(Session, {
  foreignKey: "session_id"
});

Question.hasMany(Response,{
    foreignKey: "question_id"

})
Response.belongsTo(Question, {
  foreignKey:"question_id"
});

Question.hasMany(Question_prop, {
  foreignKey: "question_id"
})
Question_prop.belongsTo(Question, {
  foreignKey: "question_id"
});

Question.hasMany(Alternative, {
  foreignKey: "question_id"
})
Alternative.belongsTo(Question, {
  foreignKey: "question_id"
});

Alternative.hasMany(Alternative_prop,{
  foreignKey: "alternative_id"
})
Alternative_prop.belongsTo(Alternative, {
  foreignKey: "alternative_id"
});

sequelize.authenticate()
.then(() => console.log("DB connected"))
.catch(err => console.log(`ERROR${err}`));



(async () => {
  await sequelize.sync({ force: true });
 
  user_json.forEach(async (element) =>{ const user = await User.create(element)  })
  poll_json.forEach(async (element) =>{ await Poll.create(element)})
  poll_include_json.forEach(async (element) =>{ await Include.create(element)}) 
  prop_ison.forEach(async (element) =>{ await Prop.create(element)})
  question_json.forEach(async (element) =>{ await Question.create(element)})  
  question_prop_json.forEach(async (element) =>{ await Question_prop.create(element)}) 
  alternative_json.forEach(async (element) =>{ await Alternative.create(element)}) 
  alternative_prop_json.forEach(async (element) =>{ await Alternative_prop.create(element)}) 
  session_json.forEach(async (element) =>{ await Session.create(element)}) 
  response_json.forEach(async (element) =>{ await Response.create(element)})
  response_prop_json.forEach(async (element) =>{ await Response_prop.create(element)}) 


 await  User.findAll()
  /*SELECT `session`.`session_id`, `session`.`start`, `session`.`end`,
   `user`.`user_id` AS `user.user_id`, `user`.`name` AS `user.name`, 
   `poll`.`poll_id` AS `poll.poll_id`, `poll`.`name` AS `poll.name` 
  FROM `session` AS `session`
  INNER JOIN `user` AS `user` ON `session`.`user_id` = `user`.`user_id`
  INNER JOIN `poll` AS `poll` ON `session`.`poll_id` = `poll`.`poll_id`; */
  Session.findAll
  ({attributes:['start', 'end'],
        include: [
          {model:User,
            attributes:['name'],
            required: true,
            right:true},
          {
          model: Poll,
          attributes:['name'],
          required: true, 
          right:true
        }
      ]
  })    .then(function(instance){
    console.log("Експерти і опитування", JSON.stringify(instance, null, 2));
    console.table(JSON.parse(JSON.stringify(instance, null, 2)))});
    /*SELECT 
      `poll`.`poll_id`, `poll`.`name`,
      `questions`.`question_id` AS `questions.question_id`, `questions->question_props`.`id` AS `questions.question_props.id`,
      `questions->question_props`.`value` AS `questions.question_props.value`,
      `questions->alternatives`.`alternative_id` AS `questions.alternatives.alternative_id`,
      `questions->alternatives->alternative_props`.`id` AS `questions.alternatives.alternative_props.id`,
      `questions->alternatives->alternative_props`.`value` AS `questions.alternatives.alternative_props.value` 
    FROM `poll` AS `poll` 
    INNER JOIN `question` AS `questions` ON `poll`.`poll_id` = `questions`.`poll_id` 
    LEFT OUTER JOIN `question_prop` AS `questions->question_props` ON `questions`.`question_id` = `questions->question_props`.`question_id`
    INNER JOIN `alternative` AS `questions->alternatives` ON `questions`.`question_id` = `questions->alternatives`.`question_id`
    LEFT OUTER JOIN `alternative_prop` AS `questions->alternatives->alternative_props` ON `questions->alternatives`.`alternative_id` = `questions->alternatives->alternative_props`.`alternative_id`; */
  Poll.findAll(
    {attributes:['name'],
    include:[{
      model:Question,
      attributes:['question_id'],
      required: true,
      right:false,
      include:[{
        model:Question_prop,
        attributes:['value']},{
        model:Alternative,
        attributes:['alternative_id'],
        required: true,
        include:[{
          model:Alternative_prop,
          attributes:['value']
        }]
      }]
  }]}
  ).then(function(instance){
    console.log("питання і відповіді\n", JSON.stringify(instance, null, 2));
   });
})();
