# Use the latest asp.net core runtime as the base image
FROM mcr.microsoft.com/dotnet/aspnet:7.0 AS base
WORKDIR /app
EXPOSE 5260

# Use the latest asp.net core SDK as the build image
FROM mcr.microsoft.com/dotnet/sdk:7.0 AS build
WORKDIR /src
COPY ["OnlineShop.Api.csproj", "api/"]
RUN dotnet restore "api/OnlineShop.Api.csproj"

WORKDIR "/src"
COPY . .

#RUN dotnet build "OnlineShop.Api.csproj" -c Release -o /app/build
RUN dotnet build

RUN dotnet tool install --global dotnet-ef --version 7.0
ENV PATH="$PATH:/root/.dotnet/tools"
#RUN dotnet ef migrations add InitialCreate
#RUN dotnet ef database update

# Publish the project
FROM build AS publish
RUN dotnet publish "OnlineShop.Api.csproj" -c Release -o /app/publish

# Final stage/image
FROM base AS final
WORKDIR /app
COPY --from=publish /app/publish .
ENTRYPOINT ["dotnet", "OnlineShop.Api.dll"]