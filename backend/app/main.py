from fastapi import FastAPI, Depends, HTTPException
from contextlib import asynccontextmanager
from sqlmodel import Session, select
from fastapi.middleware.cors import CORSMiddleware


from app.models import Users
from app.schemas import UserCreate, UserLogin
from app.db import get_session, init_db
from app.auth import hash_password, verify_password

@asynccontextmanager
async def lifespan(app: FastAPI):
    init_db()
    yield


app = FastAPI(lifespan=lifespan)

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)



@app.post("/register")
def register(user: UserCreate, session: Session = Depends(get_session)):
    exsiting_user = session.exec(select(Users).where(Users.email == user.email)).first()
    if exsiting_user:
        raise HTTPException(status_code=400, detail="Email already registered")
    
    new_user = Users(
        email=user.email,
        password=hash_password(user.password)
    )

    session.add(new_user)
    session.commit()
    session.refresh(new_user)

    return {"message": "User registered successfully", "user_id": new_user.id}

@app.post("/login")
def login(user: UserLogin, session: Session = Depends(get_session)):
    db_user = session.exec(select(Users).where(Users.email == user.email)).first()
    if not db_user or not verify_password(user.password, db_user.password):
        raise HTTPException(status_code=401, detail="Invalid email or password")
    return {"message": "Login succesful", "user_id": db_user.id}
