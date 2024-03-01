FROM mcr.microsoft.com/dotnet/aspnet:7.0 AS base
WORKDIR /app
EXPOSE 5071

ENV ASPNETCORE_URLS=http://+:5071

# Creates a non-root user with an explicit UID and adds permission to access the /app folder
# For more info, please refer to https://aka.ms/vscode-docker-dotnet-configure-containers
RUN adduser -u 5678 --disabled-password --gecos "" appuser && chown -R appuser /app
USER appuser

FROM --platform=$BUILDPLATFORM mcr.microsoft.com/dotnet/sdk:7.0 AS build
ARG configuration=Release
WORKDIR /src
COPY ["movie-theater-backend.csproj", "./"]
RUN dotnet restore "movie-theater-backend.csproj"
COPY . .
WORKDIR "/src/."
RUN dotnet build "movie-theater-backend.csproj" -c $configuration -o /app/build

FROM build AS publish
ARG configuration=Release
RUN dotnet publish "movie-theater-backend.csproj" -c $configuration -o /app/publish /p:UseAppHost=false

#RUN dotnet tool install --global dotnet-ef --version 7.0.5
#ENV PATH="${PATH}:/root/.dotnet/tools"
#RUN dotnet ef database update

FROM base AS final
WORKDIR /app
COPY --from=publish /app/publish .
ENTRYPOINT ["dotnet", "movie-theater-backend.dll"]
